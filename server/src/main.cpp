#include <iostream>

#include "Master.h"
using namespace std;

int main() {
    Config config;
    //TODO make it configuable
    config.host="127.0.0.1";
    config.port=33015;
    config.max_clients=100;
    config.num_workers=5;
    DbConfig db_config;

    db_config.user="root";
    db_config.password="root";
    db_config.database = "ExchangeSimulator";
    db_config.host = "tcp://127.0.0.1:3306";

    config.db_config=db_config;
    Master master(&config);
    master.start();

    return 0;
}