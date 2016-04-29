#ifndef EXCHANGESIMULATOR_SERVER_ORDERBOOK_H
#define EXCHANGESIMULATOR_SERVER_ORDERBOOK_H


#include "Quote.h"

#include <vector>
#include <string>
#include <include/Common.h>
#include <cppconn/statement.h>


class OrderBook {
public:

    OrderBook(std::string symbol, std::shared_ptr<sql::Statement> stmt) : symbol_(symbol), stmt_(stmt) { }

    ~OrderBook();

    void put(const Quote &quote);

    const std::vector<Quote> &get() const { return quotes_; }

    std::vector<Quote> &get() { return quotes_; }

    Fix42::MessagePtr execute();

private:
    std::string symbol_;
    std::vector<Quote> quotes_;
    std::shared_ptr<sql::Statement> stmt_;
    bool has_lock_ = false;

    void lock();

    void unlock();

};


#endif //EXCHANGESIMULATOR_SERVER_ORDERBOOK_H
