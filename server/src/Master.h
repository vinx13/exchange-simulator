#ifndef EXCHANGESIMULATOR_SERVER_MASTER_H
#define EXCHANGESIMULATOR_SERVER_MASTER_H


#include "Config.h"
#include "Worker.h"

#include <memory>
#include <vector>
#include <event2/event.h>
#include <event2/listener.h>

class Master {
public:
    static const std::string TAG;

    static std::shared_ptr<Master> getInstance();

    static void signalHandler(int signum);

    static void acceptConnection(
            struct evconnlistener *listener,
            evutil_socket_t sock,
            struct sockaddr *addr,
            int len, void *ptr
    );

    ~Master();

    void start();

    void stop();


private:
    static std::shared_ptr<Master> instance__;

    std::vector<std::shared_ptr<Worker>> workers_;
    event_base *event_base_ = nullptr;
    evconnlistener *evconn_listener_ = nullptr;

    int next_worker_;

    Master();


};


#endif //EXCHANGESIMULATOR_SERVER_MASTER_H
