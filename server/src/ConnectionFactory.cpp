#include "ConnectionFactory.h"

std::shared_ptr<ConnectionFactory> ConnectionFactory::instance__;

std::shared_ptr<ConnectionFactory> ConnectionFactory::getInstance() {
    return instance__;
}

void ConnectionFactory::init(const DbConfig &config) {
    instance__ = std::shared_ptr<ConnectionFactory>(new ConnectionFactory(config));
}

ConnectionFactory::ConnectionFactory(const DbConfig &config):config_(config){
    driver_ = sql::mysql::get_mysql_driver_instance();
}

ConnectionFactory::ConnectionPtr ConnectionFactory::createConnnection() {
    std::lock_guard<std::mutex> lock(mutex_);

    auto conn = std::shared_ptr<sql::Connection>(driver_->connect(config_.host, config_.user, config_.password));
    conn->setSchema(config_.database);
    conn->setAutoCommit(true);
    return conn;
}

