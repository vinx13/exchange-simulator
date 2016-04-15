#include "Master.h"

#include <arpa/inet.h>
#include <cstring>
#include <iostream>

Master::Master(const Config *config) : config_(*config) {
    event_base_ = event_base_new();
    for (int i = 0; i < config_.num_workers; i++) {
        workers_.push_back(std::make_shared<Worker>());
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

void Master::acceptConnection(struct evconnlistener *listener, evutil_socket_t sfd,
                        struct sockaddr *addr, int len, void *ptr) {

    Master *master = static_cast<Master *>(ptr);
    master->workers_[master->next_worker_++]->putConnection(sfd);
    if (master->next_worker_ == master->config_.num_workers)
        master->next_worker_ = 0;

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

