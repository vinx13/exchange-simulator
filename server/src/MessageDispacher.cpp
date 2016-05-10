#include "MessageDispacher.h"
#include "OrderBook.h"


Fix42::MessagePtr MessageDispacher::accept(const Fix42::MessagePtr message) {

    auto type = message->getType();

    switch (type) {
        case Fix42::kMessageType::kNewOrderSingle:
            return onSingleOrder(message);
            //TODO handle trade records
        default:
            return Fix42::MessagePtr();
    }
}

Fix42::MessagePtr MessageDispacher::onSingleOrder(const Fix42::MessagePtr message) {
    //TODO: catch exception when fields do not exist
    OrderBook order_book(message->getField<Fix42::kFieldName::kSymbol>()->getValue(), dbconn_);
    Quote quote(message);

    if (order_book.isValid(quote)) {
        order_book.put(quote);
        order_book.execute();
        return createMsgOrdAc(quote);
    } else {
        return createMsgOrdReject(quote);
    }
}

Fix42::MessagePtr MessageDispacher::createMsgOrdAc(const Quote &quote) {
    auto message = std::make_shared<Fix42::Message>();
    addBasicFields(quote, message);
    message->setField<Fix42::kFieldName::kOrdStatus>(0);//new
    return message;
}

Fix42::MessagePtr MessageDispacher::createMsgOrdReject(const Quote &quote) {
    auto message = std::make_shared<Fix42::Message>();
    addBasicFields(quote, message);
    message->setField<Fix42::kFieldName::kOrdStatus>(8);//reject
    return message;
}

void MessageDispacher::addBasicFields(const Quote &quote, std::shared_ptr<Fix42::Message> &message) const {
    message->setType(Fix42::kMessageType::kExecutionReport);
    message->setField<Fix42::kFieldName::kClOrdID>(quote.client_order_id);
    message->setField<Fix42::kFieldName
    ::kCumQty>(0);
    message->setField<Fix42::kFieldName::kSymbol>(quote.symbol);
    message->setField<Fix42::kFieldName::kSide>(static_cast<char>(quote.side));
    message->setField<Fix42::kFieldName::kPrice>(Quote::toOriginalPrice(quote.price));
    message->setField<Fix42::kFieldName::kOrderQty>(quote.quantity);
}