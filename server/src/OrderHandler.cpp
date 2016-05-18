#include "OrderHandler.h"
#include "OrderBook.h"

std::vector<Fix42::MessagePtr> OrderHandler::accept(const Fix42::MessagePtr message) {
    auto type = message->getType();
    std::vector<Fix42::MessagePtr> results;

    if (type == Fix42::kMessageType::kNewOrderSingle) {
        Quote quote(message);
        handleSingleOrder(quote, results);
    } else if (type == Fix42::kMessageType::kNewOrderList) {
        const auto &orders = message->getRepeatGroup(Fix42::kFieldName::kNoOrders)->getUnits();
        for (const auto order: orders) {
            Quote quote(order);
            handleSingleOrder(quote, results);
        }
    } else if (type == Fix42::kMessageType::kOrderStatusRequest) {
        return handleSingleRequest(message);
    }
    return results;
}

void OrderHandler::handleSingleOrder(const Quote &quote, std::vector<Fix42::MessagePtr> &results) {
    OrderBook orderBook(quote.symbol, api_);
    if (!orderBook.isValid(quote)) {
        results.push_back(createMsgReject(quote));
        return;
    }
    orderBook.put(quote);
    results.push_back(createMsgAccept(quote));
    orderBook.execute();
}

std::vector<Fix42::Message> OrderHandler::handleSingleRequest(const Fix42::MessagePtr message) {
    std::string client = message->getField<Fix42::kFieldName::kClientID>()->getValue(),
            client_order_id = message->getField<Fix42::kFieldName::kClOrdID>()->getValue();
    Quote original, current;

    std::vector<Fix42::MessagePtr>> results;

    if (!api_.orderBookClientQuery(client, client_order_id, current) ||
        !api_.orderArchiveClientQuery(client, client_order_id, original)) {
        return results;
    }
    auto response = std::make_shared<Fix42::Message>();
    addBasicFields(original, response);

    int executed_quantity = original.quantity - current.quantity;
    response->setField<Fix42::kFieldName::kOrdStatus>(
            executed_quantity == original.quantity ? 2 : 1); //filled or partially filled
    response->setField<Fix42::kFieldName::kCumQty>(executed_quantity);

    results.push_back(response);
    return results;
}

Fix42::MessagePtr OrderHandler::createMsgAccept(const Quote &quote) {
    auto message = std::make_shared<Fix42::Message>();
    addBasicFields(quote, message);
    message->setField<Fix42::kFieldName::kCumQty>(0);
    message->setField<Fix42::kFieldName::kOrdStatus>(0);//new
    return message;
}

Fix42::MessagePtr OrderHandler::createMsgReject(const Quote &quote) {
    auto message = std::make_shared<Fix42::Message>();
    addBasicFields(quote, message);
    message->setField<Fix42::kFieldName::kCumQty>(0);
    message->setField<Fix42::kFieldName::kOrdStatus>(8);//reject
    return message;
}

//add common fields of message `accept`, `reject` and `order status`
void OrderHandler::addBasicFields(const Quote &quote, std::shared_ptr<Fix42::Message> &message) const {
    message->setType(Fix42::kMessageType::kExecutionReport);
    message->setField<Fix42::kFieldName::kClOrdID>(quote.client_order_id);
    message->setField<Fix42::kFieldName::kSymbol>(quote.symbol);
    message->setField<Fix42::kFieldName::kSide>(static_cast<char>(quote.side));
    message->setField<Fix42::kFieldName::kPrice>(Quote::toOriginalPrice(quote.price));
    message->setField<Fix42::kFieldName::kOrderQty>(quote.quantity);
}

