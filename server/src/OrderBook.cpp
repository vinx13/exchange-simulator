#include "OrderBook.h"
#include <cstdlib>

#define BUFFER_SIZE 1024

OrderBook::~OrderBook() {
    if (has_lock_) {
        unlock();
    }
}

void OrderBook::put(const Quote &quote) {
    /*
     * orderbook_put(
     *  IN symbol TEXT, IN client TEXT, IN client_order_id TEXT, IN side CHAR(1), IN price INT, IN quantity INT
     *  )
     */
    char buf[BUFFER_SIZE];
    sprintf(buf, "CALL orderbook_put('%s','%s','%s','%c',%d,%d)",
            quote.symbol.c_str(), quote.client.c_str(),
            quote.client_order_id.c_str(),
            static_cast<char>(quote.side),
            quote.price, quote.quantity);
    stmt_->execute(buf);
}

Fix42::MessagePtr OrderBook::execute() {
    return std::shared_ptr<Fix42::Message>();
}

void OrderBook::lock() {
    const std::string query = "CALL security_lock('" + symbol_ + "')";
    stmt_->execute(query);
}

void OrderBook::unlock() {
    const std::string query = "CALL security_unlock('" + symbol_ + "')";
    stmt_->execute(query);
}

