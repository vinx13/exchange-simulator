#include "Client.h"
#include <fstream>
#include <iostream>
#include <unistd.h>

Client::Client(const std::string &config) {
    readConfig(config);
}

void Client::readConfig(const std::string &config) {
    std::ifstream fin(config);
    std::string key;
    while(fin >> key) {
        if (key == "host") {
            fin >> host_;
        } else if (key == "port") {
            fin >> port_;
        }
    }
}

void Client::connect() {
    sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(host_.c_str());
    sin.sin_port = htons(port_);
    server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (::connect(server_fd_, (sockaddr *) &sin, sizeof(sin)) < 0) {
        std::cout << "cannot connect to server";
        exit(EXIT_FAILURE);
    }
}

std::string Client::getCmdBody(const std::string &cmd) const {
    return cmd.substr(cmd.find(' ', 0) + 1);
}

void Client::send(const Fix42::MessagePtr message) {
    auto s = message->toString();
    ::write(server_fd_, s.c_str(), s.size());
}

Fix42::MessagePtr Client::read() {
    const int BUF_SIZE = 4096;
    char buf[BUF_SIZE];
    int len;
    if ((len = ::read(server_fd_, buf, BUF_SIZE)) > 0) {
        try {
            return std::make_shared<Fix42::Message>(std::string(buf, buf+len));
        }catch (const Fix42::MessageParserError &e){
            std::cout << e.what() << std::endl;
        }
    }
    return Fix42::MessagePtr();
}