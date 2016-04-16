#include "Master.h"

#include <arpa/inet.h>
#include <cstring>

Master::Master(const Config *config) : config_(*config) {
    event_base_ = event_base_new();

    for (int i = 0; i < config_.num_workers; i++) {
        int fds[2];
        if (socketpair(AF_UNIX, SOCK_STREAM, 0, fds) == -1) {
            //TODO: Error
        } else {
            worker_fds_.push_back(fds[0]);
            workers_.push_back(std::make_shared<Worker>(fds[1]));
        }
    }

    sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(config_.host.c_str());
    sin.sin_port = htons(config->port);
    evconn_listener_ = evconnlistener_new_bind(
            event_base_, acceptConnection, this, LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE,
            -1, (struct sockaddr *) &sin, sizeof(sin)
    );
}

void Master::acceptConnection(struct evconnlistener *listener,
                              evutil_socket_t sfd,
                              struct sockaddr *addr,
                              int len, void *ptr) {

    Master *master = static_cast<Master *>(ptr);
    int worker_id = master->next_worker_++;
    if (master->next_worker_ == master->config_.num_workers)
        master->next_worker_ = 0;

    master->workers_[worker_id]->putConnection(sfd);
    if (write(master->worker_fds_[worker_id], "", 1) == -1) {
        //TODO: Error
    }
}

Master::~Master() {
    evconnlistener_free(evconn_listener_);
    event_base_free(event_base_);
}

void Master::start() {
    for (auto &worker:workers_)
        worker->start();
    event_base_dispatch(event_base_);
}

void Master::stop() {
    for (auto &worker:workers_)
        worker->stop();
    evconnlistener_free(evconn_listener_);
    event_base_loopbreak(event_base_);
}

