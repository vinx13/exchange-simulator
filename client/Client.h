#ifndef EXCHANGESIMULATOR_CLIENT_CLIENT_H
#define EXCHANGESIMULATOR_CLIENT_CLIENT_H


#include "Fix42.h"

#include <string>
#include <arpa/inet.h>
#include <fcntl.h>

class Client {
public:
    Client(const std::string &config);

    virtual void start() = 0;

protected:
    std::string host_;
    in_port_t port_;
    int server_fd_;

    void readConfig(const std::string &config);

    void connect();

    std::string getCmdBody(const std::string &cmd) const;

    void send(const Fix42::MessagePtr message);

    Fix42::MessagePtr read();
};


#endif //EXCHANGESIMULATOR_CLIENT_CLIENT_H
