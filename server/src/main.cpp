#include <iostream>
#include <fstream>

#include "Master.h"

using namespace std;

int main() {
    Config config("config");
    Master master(&config);
    master.start();

    return 0;
}