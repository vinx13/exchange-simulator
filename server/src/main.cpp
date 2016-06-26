#include <cstring>
#include <iostream>
#include <fstream>

#include "Master.h"


int main(int argc, char **argv) {
    if (argc < 2) {
        Config::initGlobalConfig("config");
    } else if (argc == 3 && strcmp(argv[1], "-c") == 0) {
        Config::initGlobalConfig(argv[2]);
    } else {
        std::cout << "Invalid options";
        exit(EXIT_FAILURE);
    }
    Master::getInstance()->start();
    return 0;
}
