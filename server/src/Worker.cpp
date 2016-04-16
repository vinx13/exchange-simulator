#include "Worker.h"

void Worker::workerMain(Worker *worker) {
    event_base_dispatch(worker->event_base_);
}

void Worker::readRequest(evutil_socket_t fd, short what, void *arg) {

}

void Worker::registerConnection(evutil_socket_t fd, short what, void *arg) {
    Worker *worker = static_cast<Worker *>(arg);

    std::unique_lock<std::mutex> lock(worker->conn_mutex_);
    evutil_socket_t conn_fd = worker->new_conn_fds_.front();
    worker->new_conn_fds_.pop();
    worker->conn_fds_.push_back(fd);
    event *read_event = event_new(worker->event_base_, conn_fd, EV_READ | EV_PERSIST, readRequest, worker);
    event_add(read_event, NULL);
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
