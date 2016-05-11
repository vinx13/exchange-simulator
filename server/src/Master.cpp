#include "Master.h"
#include "Logger.h"

#include <arpa/inet.h>
#include <cstring>

const std::string Master::TAG("Master");

std::shared_ptr<Master> Master::instance__;

std::shared_ptr<Master> Master::getInstance() {
    if (!instance__)
        instance__.reset(new Master());
    return instance__;

}


void Master::sigintHandler(int signum) {
    if (signum == SIGABRT) {
        Logger::getLogger()->info(TAG, "Signal int received.");
        Master::getInstance()->stop();
        exit(EXIT_SUCCESS);
    }
}

Master::Master() {
    signal(SIGINT, sigintHandler);

    auto config = Config::getGlobalConfig();

    ConnectionFactory::init(config->db_config);

    next_worker_ = 0;

    event_base_ = event_base_new();

    for (int i = 0; i < config->num_workers; i++) {
        int fds[2];
        if (socketpair(AF_UNIX, SOCK_STREAM, 0, fds) == -1) {
            Logger::getLogger()->error(TAG, "failure in socket pair");
        } else {
            worker_fds_.push_back(fds[0]);
            workers_.push_back(std::make_shared<Worker>(fds[1]));
        }
    }

    sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(config->host.c_str());
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
    if (master->next_worker_ == Config::getGlobalConfig()->num_workers)
        master->next_worker_ = 0;

    master->workers_[worker_id]->putConnection(sfd);
    master->sendNewConnCmd(0);
    master->sendNewConnCmd(worker_id);
}


Master::~Master() {
    if (evconn_listener_)
        evconnlistener_free(evconn_listener_);
    if (event_base_) {
        event_base_free(event_base_);
    }
}

void Master::start() {
    for (auto &worker:workers_)
        worker->start();
    event_base_dispatch(event_base_);
}

void Master::stop() {
    sendStopCmd();
    event_base_loopbreak(event_base_);
    evconnlistener_free(evconn_listener_);
    evconn_listener_ = nullptr;
}

void Master::sendStopCmd() {
    for (const auto &worker_fd:worker_fds_) {
        if (sendCmd(worker_fd, kMasterCmd::kStop) == -1) {
            Logger::getLogger()->error(TAG, "failure in dispatching new connections");
        }
    }
}

void Master::sendNewConnCmd(const int worker_id) {
    if (sendCmd(worker_id, kMasterCmd::kNewConnection) == -1) {
        Logger::getLogger()->error(TAG, "failure in dispatching new connections");
    }
}

int Master::sendCmd(const int worker_fd, const kMasterCmd command) {
    char cmd = static_cast<char>(command);
    return write(worker_fd, &cmd, 1);
}
