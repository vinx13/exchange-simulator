#ifndef EXCHANGESIMULATOR_SERVER_CONNECTIONFACTORY_H
#define EXCHANGESIMULATOR_SERVER_CONNECTIONFACTORY_H


#include <memory>
#include <cppconn/connection.h>
#include <mysql_driver.h>

class ConnectionFactory {
public:
    typedef std::shared_ptr<sql::Connection> ConnectionPtr;

    static std::shared_ptr<ConnectionFactory> getInstance();

    static void init(const std::string &server, const std::string &user, const std::string &password);

    ConnectionPtr getConnnection();

    ConnectionFactory(const std::string &server, const std::string &user, const std::string &password);

private:
    static std::shared_ptr<ConnectionFactory> instance__;
    std::mutex mutex_;
    const std::string server_, user_, password_;
    sql::mysql::MySQL_Driver *driver_;
};


#endif //EXCHANGESIMULATOR_SERVER_CONNECTIONFACTORY_H
