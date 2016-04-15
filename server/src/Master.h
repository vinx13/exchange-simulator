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
    static void acceptConnection(
            struct evconnlistener *listener,
            evutil_socket_t sock,
            struct sockaddr *addr,
            int len, void *ptr
    );

    explicit Master(const Config *config);

    ~Master();

    void start();

    void stop();


private:
    const Config config_;
    std::vector<std::shared_ptr<Worker> > workers_;
    event_base *event_base_;
    evconnlistener *evconn_listener_;

    int next_worker_;
};


#endif //EXCHANGESIMULATOR_SERVER_MASTER_H
