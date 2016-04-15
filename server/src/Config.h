#ifndef EXCHANGESIMULATOR_SERVER_CONFIG_H
#define EXCHANGESIMULATOR_SERVER_CONFIG_H


#include <string>
#include <netinet/in.h>

struct Config {
    std::string host;
    in_port_t port;
    int num_workers;
    int max_clients;

    std::string access_log;
    std::string error_log;
};


#endif //EXCHANGESIMULATOR_SERVER_CONFIG_H
