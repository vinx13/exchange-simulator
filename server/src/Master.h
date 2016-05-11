#ifndef EXCHANGESIMULATOR_SERVER_MASTER_H
#define EXCHANGESIMULATOR_SERVER_MASTER_H


#include "Config.h"
#include "Worker.h"

#include <memory>
#include <vector>
#include <event2/event.h>
#include <event2/listener.h>

enum class kMasterCmd : char {
    kNewConnection = 'n', kStop = 'q'
};

class Master {
public:
    static const std::string TAG;

    static std::shared_ptr<Master> getInstance();

    static void sigintHandler(int signum);

    static void acceptConnection(
            struct evconnlistener *listener,
            evutil_socket_t sock,
            struct sockaddr *addr,
            int len, void *ptr
    );

    Master();

    ~Master();

    void start();

    void stop();


private:
    static std::shared_ptr<Master> instance__;


    std::vector<std::shared_ptr<Worker> > workers_;
    std::vector<evutil_socket_t> worker_fds_;
    event_base *event_base_ = nullptr;
    evconnlistener *evconn_listener_ = nullptr;

    int next_worker_;

    int sendCmd(const int worker_fd, const kMasterCmd command);

    void sendStopCmd();

    void sendNewConnCmd(const int worker_id);
};


#endif //EXCHANGESIMULATOR_SERVER_MASTER_H
