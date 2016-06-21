#include "Worker.h"
#include "Fix42.h"
#include "Logger.h"
#include "Master.h"
#include <string>

static const std::string EXPECT_HEADER = "8=FIX.4.2\0019=";
static const int EXPECT_HEADER_LEN = 12;
/*EXPECT_HEADER.length();*/

const std::string Worker::TAG("Worker");

struct BufferContext {
    Worker *worker;
    std::vector<char> data;
    int header_cur_pos;
    int body_remained_len;

    BufferContext(Worker *worker) : worker(worker) { reset(); }

    void reset() {
        data.clear();
        header_cur_pos = 0;
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

void Worker::deregisterConnection(bufferevent *bev) {
    bufferevent_free(bev);

}

void Worker::bevOnError(bufferevent *bev, short what, void *arg) {
    Logger::getLogger()->error(TAG, "bufferevent error code " + std::to_string(what));
    if (what & BEV_EVENT_EOF) {
        static_cast<Worker *>(arg)->deregisterConnection(bev);
    }
}

void Worker::bevOnRead(bufferevent *bev, void *arg) {
    BufferContext *context = static_cast<BufferContext *>(arg);
    const int BUF_SIZE = 1024;
    char buf[BUF_SIZE];
    int len = bufferevent_read(bev, buf, BUF_SIZE);
    Logger::getLogger()->debug(TAG, "message received. " + std::string(buf, buf + len));
    context->worker->processInput(bev, buf, len, context);
    //bufferevent_write(bev, "hello", 5); //FIXME
}

void Worker::bevOnWrite(bufferevent *bev, void *arg) {
}


Worker::~Worker() {
    for (auto context:buffer_contexts_)
        delete context;
}

void Worker::onOwnerSignal(evutil_socket_t fd, short what, void *arg) {
    Worker *worker = static_cast<Worker *>(arg);
    char c;
    read(fd, &c, 1);
    auto cmd = static_cast<kWorkerSignal>(c);
    if (cmd == kWorkerSignal::kNewConnection)
        worker->registerConnection(fd);
    else if (cmd == kWorkerSignal::kStop) {
        worker->stopEventLoop();
    }
}

void Worker::stopEventLoop() { event_base_loopbreak(event_base_); }

void Worker::registerConnection(int fd) {
    Logger::getLogger()->info(TAG, "connection received " + std::to_string(fd));

    std::unique_lock<std::mutex> lock(conn_mutex_);
    while (!new_conn_fds_.empty()) {
        evutil_socket_t conn_fd = new_conn_fds_.front();
        new_conn_fds_.pop();
        evutil_make_socket_nonblocking(conn_fd);
        bufferevent *client_bev = bufferevent_socket_new(event_base_, conn_fd, BEV_OPT_CLOSE_ON_FREE);
        bufferevent_setwatermark(client_bev, EV_READ, 0/*FIXME*/, 0 /* unlimited */);
        bufferevent_setcb(client_bev,
                          bevOnRead, bevOnWrite, bevOnError,
                          bufferContextAlloc()/*arg passed to callback*/);
        bufferevent_enable(client_bev, EV_READ | EV_WRITE);

        conn_bevs_.push_back(client_bev);
    }
}

Worker::Worker() :
        dbconn_(ConnectionFactory::getInstance()->createConnnection()),
        dispatcher_(dbconn_) {

    int fds[2];
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, fds) == -1) {
        Logger::getLogger()->error(TAG, "failure in socket pair");
    } else {
        worker_owner_fd_ = fds[0];
        worker_thread_fd_ = fds[1];
    }

    event_base_ = event_base_new();
    event_master_cmd_ = event_new(event_base_, worker_thread_fd_, EV_READ | EV_PERSIST, onOwnerSignal, this);
    event_add(event_master_cmd_, NULL);
}

void Worker::start() {
    worker_thread_ = std::unique_ptr<std::thread>(new std::thread(workerMain, this));
}

void Worker::stop() {
    notifyStop();
    worker_thread_->join();
}

void Worker::putConnection(evutil_socket_t sfd) {
    {//synchronized
        std::unique_lock<std::mutex> lock(conn_mutex_);
        new_conn_fds_.push(sfd);
    }
    notifyNewConn();
}

void Worker::processInput(bufferevent *bev, const char *buf, const int len, BufferContext *context) {
    int processed = 0;
    while (processed < len) {
        if (context->header_cur_pos < EXPECT_HEADER_LEN) {
            if (EXPECT_HEADER[context->header_cur_pos++] == buf[processed]) {
                context->data.push_back(buf[processed++]);
            } else {
                //TODO: Error
                //goto next valid character
                context->reset();
                while (++processed < len && buf[processed] != 1);
                ++processed;
            }
        } else if (context->body_remained_len == -1) {
            if (isdigit(buf[processed])) {
                context->data.push_back(buf[processed++]);
            } else if (buf[processed] == 1) {
                context->data.push_back(buf[processed++]);
                auto start = context->data.begin() + EXPECT_HEADER_LEN;
                auto end = context->data.end();
                context->body_remained_len = std::stoi(std::string(start, end));
            } else {
                //TODO: Error
                context->reset();
                while (++processed < len && buf[processed] != 1);
                ++processed;
            }
        } else {
            context->data.push_back(buf[processed++]);
            if (--context->body_remained_len == 0) {
                std::string s(context->data.begin(), context->data.end());
                auto results = dispatcher_.dispatch(
                        std::make_shared<Fix42::Message>(s)
                );
                for (const auto result: results) {
                    auto str_result = result->toString();
                    bufferevent_write(bev, str_result.c_str(), str_result.size());
                }
                context->reset();
            }
        }
    }
}

void Worker::notifyStop() {
    if (sendSignal(kWorkerSignal::kStop) == -1) {
        Logger::getLogger()->error(TAG, "failure in dispatching new connections");
        exit(EXIT_FAILURE);
    }
}

void Worker::notifyNewConn() {
    if (sendSignal(kWorkerSignal::kNewConnection) == -1) {
        Logger::getLogger()->error(TAG, "failure in dispatching new connections");
    }
}

int Worker::sendSignal(const kWorkerSignal command) {
    char cmd = static_cast<char>(command);
    return write(worker_owner_fd_, &cmd, 1);
}
