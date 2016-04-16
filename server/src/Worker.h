#ifndef EXCHANGESIMULATOR_SERVER_WORKER_H
#define EXCHANGESIMULATOR_SERVER_WORKER_H


#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>


struct BufferContext;

class Worker {
public:

    static void workerMain(Worker *worker);

    static void registerConnection(evutil_socket_t fd, short what, void *arg);

    static void readBuffer(bufferevent *bev, void *arg);


    Worker(evutil_socket_t notify_conn_fd);

    ~Worker();

    void start();

    void stop();

    void putConnection(evutil_socket_t fd);

    BufferContext *bufferContextAlloc();

    void processInput(const char *buf, const int len, BufferContext *context);

private:
    std::unique_ptr<std::thread> worker_thread_;
    std::vector<evutil_socket_t> conn_fds_;
    std::queue<evutil_socket_t> new_conn_fds_;
    std::mutex conn_mutex_;
    evutil_socket_t notify_conn_fd_;
    event_base *event_base_;
    std::vector<BufferContext *> buffer_contexts_;
};


#endif //EXCHANGESIMULATOR_SERVER_WORKER_H
