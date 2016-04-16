#include "Worker.h"
#include <string>

static const std::string EXPECT_HEADER = "8=FIX.4.2\0019=";
static const int EXPECT_HEADER_LEN = EXPECT_HEADER.length();

struct BufferContext {
    Worker *worker;
    std::vector<char> data;
    int header_cur_pos;
    int header_remained_len;
    int body_remained_len;

    BufferContext(Worker *worker) : worker(worker) { reset(); }

    void reset() {
        data.clear();
        header_cur_pos = 0;
        header_remained_len = EXPECT_HEADER_LEN;
        body_remained_len = -1;
    }
};

BufferContext *Worker::bufferContextAlloc() {
    BufferContext *context = new BufferContext(this);
    buffer_contexts_.push_back(context);
    return context;
}

void Worker::workerMain(Worker *worker) {
    event_base_dispatch(worker->event_base_);
}

void Worker::readBuffer(bufferevent *bev, void *arg) {
    BufferContext *context = static_cast<BufferContext *>(arg);

    if (context->header_remained_len > 0) {
        char buf[EXPECT_HEADER_LEN];
        int read_len = bufferevent_read(bev, buf, context->header_remained_len);
        bool invalid = false; //FIXME: Encapsulate as a function
        for (int i = 0; i < read_len; i++) {
            if (buf[i] != EXPECT_HEADER[context->header_cur_pos++]) {
                invalid = true;
            }
        }
        if (invalid) {
            context->reset();
            //TODO: Process error
        } else {

            context->header_remained_len -= read_len;
            context->data.insert(context->data.end(), buf, buf + read_len);
        }
    }
    if (context->header_remained_len == 0 && context->body_remained_len == -1) {
        char c;
        int read_len;
        while ((read_len = bufferevent_read(bev, &c, 1))) {
            if (isdigit(c)) {
                context->data.push_back(c);
            } else if (c == '\001') {
                context->data.push_back(c);
                auto start = context->data.begin() + EXPECT_HEADER_LEN;
                auto end = context->data.end();
                context->body_remained_len = std::stoi(std::string(start, end));
                break;
            }
        }
    }
    if (context->body_remained_len > 0) {
        const int BUFFER_SIZE = 1024;
        char buf[BUFFER_SIZE];
        int read_len = bufferevent_read(bev, buf, std::min(BUFFER_SIZE, context->body_remained_len));
        context->body_remained_len -= read_len;
        context->data.insert(context->data.end(), buf, buf + read_len);
        if (context->body_remained_len == 0) {
            //TODO: process message
            context->reset();
        }
    }
}

Worker::~Worker() {
    for (auto context:buffer_contexts_)
        delete context;
}

void Worker::registerConnection(evutil_socket_t fd, short what, void *arg) {
    Worker *worker = static_cast<Worker *>(arg);

    std::unique_lock<std::mutex> lock(worker->conn_mutex_);
    while (!worker->new_conn_fds_.empty()) {
        evutil_socket_t conn_fd = worker->new_conn_fds_.front();
        worker->new_conn_fds_.pop();
        worker->conn_fds_.push_back(fd);

        evutil_make_socket_nonblocking(conn_fd);
        bufferevent *read_bev = bufferevent_socket_new(worker->event_base_, conn_fd, BEV_OPT_CLOSE_ON_FREE);
        bufferevent_setwatermark(read_bev, EV_READ, 1/*FIXME*/, 0 /* unlimited */);
        bufferevent_setcb(read_bev, readBuffer, NULL /* FIXME: writeBuffer */, NULL /*Fixme: process error*/,
                          worker->bufferContextAlloc());
        bufferevent_enable(read_bev, EV_READ | EV_WRITE);
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
    worker_thread_->join();//Fixme: this doesn't work
}

void Worker::putConnection(evutil_socket_t sfd) {
    std::unique_lock<std::mutex> lock(conn_mutex_);
    new_conn_fds_.push(sfd);
    lock.unlock();
}

