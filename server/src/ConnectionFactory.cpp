#include "ConnectionFactory.h"

std::shared_ptr<ConnectionFactory> ConnectionFactory::getInstance() {
    return instance__;
}

void ConnectionFactory::init(const std::string &server, const std::string &user, const std::string &password) {
    instance__ = std::make_shared<ConnectionFactory>(server, user, password);
}

ConnectionFactory::ConnectionFactory(const std::string &server, const std::string &user, const std::string &password) :
        server_(server), user_(user), password_(password) {
    driver_ = sql::mysql::get_mysql_driver_instance();
}

ConnectionPtr ConnectionFactory::getConnnection() {
    std::lock_guard lock(mutex_);
    return std::shared_ptr(driver_->connect(server_,user_,password_));
}

