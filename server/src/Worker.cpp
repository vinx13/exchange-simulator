#include "Worker.h"

void Worker::workerMain(Worker *worker) {
    event_base_dispatch(worker->event_base_);
}

void Worker::readRequest(evutil_socket_t fd, short what, void *arg) {

}

void Worker::readBuffer(bufferevent *bev, short events, void *arg) {
    
}

void Worker::registerConnection(evutil_socket_t fd, short what, void *arg) {
    Worker *worker = static_cast<Worker *>(arg);

    std::unique_lock<std::mutex> lock(worker->conn_mutex_);
    while (!worker->new_conn_fds_.empty()) {
        evutil_socket_t conn_fd = worker->new_conn_fds_.front();
        worker->new_conn_fds_.pop();
        worker->conn_fds_.push_back(fd);
        /*
        event *read_event = event_new(worker->event_base_, conn_fd, EV_READ | EV_PERSIST, readRequest, worker);
        event_add(read_event, NULL);
         */

        //use buffer
        evutil_make_socket_nonblocking(conn_fd);
        bufferevent *read_bev = bufferevent_socket_new(worker->event_base_, conn_fd, BEV_OPT_CLOSE_ON_FREE);
        const int BUFFER_LEAST_BYTES = 1; //FIXME
        bufferevent_setwatermark(read_bev,EV_READ, BUFFER_LEAST_BYTES, 0 /* unlimited */);
        bufferevent_setcb(read_bev,readBuffer,NULL /* FIXME: writeBuffer */, NULL /*Fixme: process error*/, this);
    }
}

Worker::Worker(evutil_socket_t notify_conn_fd) : notify_conn_fd_(notify_conn_fd) {
    event_base_ = event_base_new();
    event *new_conn_event = event_new(event_base_, notify_conn_fd_, EV_READ | EV_PERSIST, registerConnection, this);
    event_add(new_conn_event, NULL);
}

void Worker::start() {
    worker_thread_ = std::unique_ptr<std::thread>(new std::thread(workerMain, this));
}

void Worker::stop() {
    worker_thread_->join();
}

void Worker::putConnection(evutil_socket_t sfd) {
    std::unique_lock<std::mutex> lock(conn_mutex_);
    new_conn_fds_.push(sfd);
    lock.unlock();
}

