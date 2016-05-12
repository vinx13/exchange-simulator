#include "OrderBook.h"
#include "APIUtil.h"

const double OrderBook::MAX_PRICE_DELTA = 0.1;
const double OrderBook::MAX_ORDER_VOLUMN = 0.05;

OrderBook::OrderBook(std::string symbol, APIUtil api) : api_(api) {
    loadStatus();
}

void OrderBook::loadStatus() { api_.securityQuery(symbol_, security_status_); }

OrderBook::~OrderBook() {
    if (has_lock_) {
        unlock();
    }
}

void OrderBook::put(const Quote &quote) {
    api_.orderbookPut(quote);
}

void OrderBook::lock() {
    bool locked = false;
    do {
        api_.securityTryLock(symbol_, locked);
    } while (!locked);
    has_lock_ = true;
}

void OrderBook::unlock() {
    api_.securityUnlock(symbol_);
    has_lock_ = false;
}

std::shared_ptr<std::vector<TradeRecord>> OrderBook::execute() {
    static const std::shared_ptr<std::vector<TradeRecord>> NONE;

    bool is_running = false;
    api_.systemStatusIsRunning(is_running);
    if (!is_running) {
        return NONE;
    }

    lock();
    loadStatus();
    if (!security_status_.trading) {
        return NONE;
    }
    auto records = doTrade();

    unlock();

    for (auto &record: *records) {
        api_.tradeRecordPut(record);
    }
    return records;
}

std::shared_ptr<std::vector<TradeRecord>> OrderBook::doTrade() {
    std::queue<Quote> buy_quotes, sell_quotes;
    auto records = std::make_shared<std::vector<TradeRecord>>();
    match(buy_quotes, sell_quotes);

    //buy/sell_quotes are sorted by price and time descending order
    while (!buy_quotes.empty() && !sell_quotes.empty()) {
        if (buy_quotes.front().price == sell_quotes.front().price) {

            auto &buy = buy_quotes.front();
            auto &sell = sell_quotes.front();
            TradeRecord record;

            int qty = std::__1::min(buy.quantity, sell.quantity);
            buy.quantity -= qty;
            sell.quantity -= qty;

            //TODO what if failed
            updateQuote(buy);
            updateQuote(sell);
            security_status_.price = buy.price;
            updatePrice();

            record.price = buy.price;
            record.quantity = qty;
            record.order_buy = buy.id;
            record.order_sell = sell.id;
            records->push_back(record);

            if (buy.quantity == 0) {
                buy_quotes.pop();
            }
            if (sell.quantity == 0) {
                sell_quotes.pop();
            }

        } else if (buy_quotes.front().price < sell_quotes.front().price) {
            sell_quotes.pop();
        } else { /* buy_quotes.front().price > sell_quotes.front().price */
            buy_quotes.pop();
        }

    }
    return records;
}

void OrderBook::match(std::queue<Quote> &buy, std::queue<Quote> &sell) {
    APIUtil::ResultSetPtr results;
    api_.orderbookQueryMatch(symbol_, results);

    while (results->next()) {
        Quote quote(results);
        if (quote.side == kTradeSide::kBuy) {
            buy.push(quote);
        } else if (quote.side == kTradeSide::kSell) {
            sell.push(quote);
        }
    }
}

void OrderBook::updateQuote(const Quote &quote) {
    if (quote.quantity == 0) {
        api_.orderbookDelete(quote.id);
    } else {
        api_.orderbookUpdate(quote.id, quote.quantity);
    }
}

void OrderBook::updatePrice() {
    api_.securityUpdatePrice(security_status_);
}

bool OrderBook::isValid(const Quote &quote) const {
    int prev = security_status_.prev_close;
    int delta = prev * MAX_PRICE_DELTA;
    if (quote.price < prev - delta || quote.price > prev + delta) {
        return false;
    }
    if (quote.quantity * quote.price > security_status_.market_cap * MAX_ORDER_VOLUMN) {
        return false;
    }
    return true;
}
