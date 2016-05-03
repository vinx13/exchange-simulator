#include "MessageHandler.h"
#include "OrderBook.h"


Fix42::MessagePtr MessageHandler::accept(const Fix42::MessagePtr message) {

    auto type = message->getType();

    switch (type) {
        case Fix42::kMessageType::kNewOrderSingle:
            return handleSingleOrder(message);

        default:
            return Fix42::MessagePtr();
    }
}

Fix42::MessagePtr MessageHandler::handleSingleOrder(const Fix42::MessagePtr message) {
    //TODO: catch exception when fields do not exist
    OrderBook order_book(message->getField<Fix42::kFieldName::kSymbol>()->getValue(),
                         std::shared_ptr<sql::Statement>(dbconn_->createStatement()));
    Quote quote(message);
    order_book.put(quote);
    return order_book.execute();
}