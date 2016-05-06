#include "Config.h"
#include <map>
#include <sstream>

template<class T>
static void readInto(const std::string &name, const std::map<std::string, std::string> &src, T &dest) {
    if (src.find(name) != src.end()) {
        std::istringstream sin(src.at(name));
        sin >> dest;
    }
}

Config::Config(std::istream &in) {
    std::string line;
    std::map<std::string, std::string> pairs;
    std::string k, v;
    while (std::getline(in, line)) {
        std::istringstream sin(line);
        sin >> k >> v;
        pairs[k] = v;
    }

    std::string db_host, db_user, db_password, db_database;
#define READ_OPTION(NAME) do{readInto(#NAME, pairs, NAME);}while(0);

    READ_OPTION(host)
    READ_OPTION(port)
    READ_OPTION(max_clients)
    READ_OPTION(num_workers)
    READ_OPTION(db_host)
    READ_OPTION(db_user)
    READ_OPTION(db_password)
    READ_OPTION(db_database)
    READ_OPTION(access_log)
    READ_OPTION(error_log)

#undef READ_OPTION
    db_config.host = db_host;
    db_config.user = db_user;
    db_config.password = db_password;
    db_config.database = db_database;

}