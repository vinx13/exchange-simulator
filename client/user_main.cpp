#include "UserClient.h"

int main(){
    UserClient client("config");
    client.start();
    return 0;
};