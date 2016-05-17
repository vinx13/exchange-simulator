#ifndef EXCHANGESIMULATOR_CLIENT_USERCLIENT_H
#define EXCHANGESIMULATOR_CLIENT_USERCLIENT_H


#include "Client.h"
#include <string>

class UserClient : public Client {
public:
    UserClient(const std::string &config);

    virtual void start() override;

    bool isvalid(const std::string &cmd);

    void printUsage() const;

private:
    std::string client_;

    void readClientName();

    void onQueryQuote(const std::string &cmd);

    void onBuy(const std::string &cmdbody);

    void onSell(const std::string &cmdbody);

    Fix42::MessagePtr generateOrder(const std::string &cmdbody);

    void onQueryOrder(const std::string &cmdbody);

    void doMainLoop();

    void onQueryList();

    void handleCmd(const std::string &cmd);

    bool isOrderAccepted(Fix42::MessagePtr message);
};


#endif //EXCHANGESIMULATOR_CLIENT_USERCLIENT_H
