#ifndef EXCHANGESIMULATOR_SERVER_WORKER_H
#define EXCHANGESIMULATOR_SERVER_WORKER_H


#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <event2/event.h>

class Worker {
public:
    static void workerMain(Worker *worker);

    static void registerConnection(evutil_socket_t fd, short what, void *arg);

    static void readRequest(evutil_socket_t fd, short what, void *arg);

    Worker(evutil_socket_t notify_conn_fd);

    void start();

    void stop();

    void putConnection(evutil_socket_t fd);

private:
    std::unique_ptr<std::thread> worker_thread_;
    std::vector<evutil_socket_t> conn_fds_;
    std::queue<evutil_socket_t> new_conn_fds_;
    std::mutex conn_mutex_;
    evutil_socket_t notify_conn_fd_;
    event_base *event_base_;
};


#endif //EXCHANGESIMULATOR_SERVER_WORKER_H
