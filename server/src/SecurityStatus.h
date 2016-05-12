#ifndef EXCHANGESIMULATOR_SERVER_SECURITYSTATUS_H
#define EXCHANGESIMULATOR_SERVER_SECURITYSTATUS_H


#include <string>
#include <memory>
#include <cppconn/resultset.h>

enum class kSecurityTradingStatus : int {
    kOpen = 0, kClose = 1, kHold = 2
};

struct SecurityStatus {
    std::string symbol;
    int price, prev_close, market_cap;
    bool trading;
    kSecurityTradingStatus trading_status;

    SecurityStatus() = default;

    SecurityStatus(std::shared_ptr<sql::ResultSet> res) {
        symbol = res->getString("symbol");
        price = res->getInt("price");
        prev_close = res->getInt("prev_close");
        market_cap = res->getInt("mkt_cap");
        trading_status = static_cast<kSecurityTradingStatus>(res->getInt("trading_status"));
    }
};


#endif //EXCHANGESIMULATOR_SERVER_SECURITYSTATUS_H
