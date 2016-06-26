#include "Master.h"
#include "Logger.h"

#include <signal.h>
#include <arpa/inet.h>
#include <cstring>
#include <sstream>

const std::string Master::TAG("Master");

std::shared_ptr<Master> Master::instance__;

std::shared_ptr<Master> Master::getInstance() {
    if (!instance__)
        instance__.reset(new Master());
    return instance__;
}

void Master::signalHandler(int signum) {
    std::ostringstream s;
    s << "Signal " << signum << " received.";
    Logger::getLogger()->info(TAG, s.str());

    Master::getInstance()->stop();
    Master::getInstance().reset();
    exit(EXIT_SUCCESS);

}

Master::Master() {
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    auto config = Config::getGlobalConfig();

    ConnectionFactory::init(config->db_config);

    next_worker_ = 0;

    event_base_ = event_base_new();

    for (int i = 0; i < config->num_workers; i++) {
        workers_.push_back(std::make_shared<Worker>());
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
}


Master::~Master() {
    if (evconn_listener_)
        evconnlistener_free(evconn_listener_);
    if (event_base_) {
        event_base_free(event_base_);
    }
}

void Master::start() {
    Logger::getLogger()->info(TAG, "started");
    for (auto &worker:workers_)
        worker->start();
    event_base_dispatch(event_base_);
}

void Master::stop() {
    for (auto &worker:workers_) {
        worker->stop();
    }
    event_base_loopbreak(event_base_);
    evconnlistener_free(evconn_listener_);
    evconn_listener_ = nullptr;
    Logger::getLogger()->info(TAG, "stopped");
}

