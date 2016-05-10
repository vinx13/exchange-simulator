#ifndef EXCHANGESIMULATOR_SERVER_ORDERBOOK_H
#define EXCHANGESIMULATOR_SERVER_ORDERBOOK_H


#include "Quote.h"
#include "Fix42.h"
#include "TradeRecord.h"
#include "SecurityStatus.h"
#include "APIUtil.h"

#include <vector>
#include <string>
#include <memory>
#include <queue>
#include <cppconn/statement.h>
#include <cppconn/connection.h>

class OrderBook {
public:
    static const double MAX_PRICE_DELTA;
    static const double MAX_ORDER_VOLUMN;

    OrderBook(std::string symbol, APIUtil::ConnPtr conn);

    ~OrderBook();

    void put(const Quote &quote);

    const std::vector<Quote> &get() const { return quotes_; }

    std::vector<Quote> &get() { return quotes_; }

    std::shared_ptr<std::vector<TradeRecord>> execute();

    bool isValid(const Quote &quote) const;

private:
    std::string symbol_;
    std::vector<Quote> quotes_;
    SecurityStatus security_status_;
    APIUtil::ConnPtr conn_;
    APIUtil api_;

    bool has_lock_ = false;

    void lock();

    void unlock();

    void match(std::queue<Quote> &buy, std::queue<Quote> &sell);

    void updateQuote(const Quote &quote);

    void updatePrice();

    void loadStatus();

    std::shared_ptr<std::vector<TradeRecord>> doTrade();
};


#endif //EXCHANGESIMULATOR_SERVER_ORDERBOOK_H
