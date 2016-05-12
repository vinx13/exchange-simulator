#ifndef EXCHANGESIMULATOR_SERVER_CONNECTIONFACTORY_H
#define EXCHANGESIMULATOR_SERVER_CONNECTIONFACTORY_H


#include "Config.h"

#include <memory>
#include <cppconn/connection.h>
#include <mysql_driver.h>

class ConnectionFactory {
public:
    typedef std::shared_ptr<sql::Connection> ConnectionPtr;

    static std::shared_ptr<ConnectionFactory> getInstance();

    static void init(const DbConfig &config);

    ConnectionPtr createConnnection();

private:
    static std::shared_ptr<ConnectionFactory> instance__;
    std::mutex mutex_;
    const DbConfig config_;
    sql::mysql::MySQL_Driver *driver_;

    ConnectionFactory(const DbConfig &config);
};


#endif //EXCHANGESIMULATOR_SERVER_CONNECTIONFACTORY_H
