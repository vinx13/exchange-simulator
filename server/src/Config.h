#ifndef EXCHANGESIMULATOR_SERVER_CONFIG_H
#define EXCHANGESIMULATOR_SERVER_CONFIG_H


#include <istream>
#include <string>
#include <netinet/in.h>
#include <memory>

struct DbConfig{
    std::string host, user, password, database;
};

struct Config {
    std::string host;
    in_port_t port;
    int num_workers;
    int max_clients;
    bool debug;

    std::string access_log;
    std::string error_log;

    DbConfig db_config;

    static std::shared_ptr<Config> getGlobalConfig(){return instance__;}
    static void initGlobalConfig(const std::string &filename);
private:
    static std::shared_ptr<Config> instance__;

    Config(const std::string &filename);

};

#endif //EXCHANGESIMULATOR_SERVER_CONFIG_H
