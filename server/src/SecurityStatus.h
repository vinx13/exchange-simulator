#ifndef EXCHANGESIMULATOR_SERVER_SECURITYSTATUS_H
#define EXCHANGESIMULATOR_SERVER_SECURITYSTATUS_H


#include <string>
#include <memory>
#include <cppconn/resultset.h>

struct SecurityStatus {
    std::string symbol;
    int price, prev_close, market_cap;
    bool trading;

    SecurityStatus() = default;

    SecurityStatus(std::shared_ptr<sql::ResultSet> res) {
        symbol = res->getString("symbol");
        price = res->getInt("price");
        prev_close = res->getInt("prev_close");
        market_cap = res->getInt("mkt_cap");
        trading = res->getBoolean("trading");
    }
};


#endif //EXCHANGESIMULATOR_SERVER_SECURITYSTATUS_H
