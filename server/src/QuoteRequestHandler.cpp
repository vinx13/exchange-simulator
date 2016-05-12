#include "QuoteRequestHandler.h"

std::vector<Fix42::MessagePtr> QuoteRequestHandler::accept(const Fix42::MessagePtr message) {
    std::vector<Fix42::MessagePtr> results;
    auto requests = message->getRepeatGroup(Fix42::kFieldName::kNoRelatedSym)->getUnits();
    for (const auto &request : requests) {
        auto symbol = request->getField<Fix42::kFieldName::kSymbol>()->getValue();
        querySingle(symbol, results);
    }
    return results;
}

void QuoteRequestHandler::querySingle(const std::string &symbol, std::vector<Fix42::MessagePtr> &results) {
    Quote buy_quote, sell_quote;
    bool success;
    success = api_.orderBookQuery(symbol, kTradeSide::kBuy, true, buy_quote);
    success &= api_.orderBookQuery(symbol, kTradeSide::kSell, false, sell_quote);
    if (!success) {
        return;
    }
    auto message = std::make_shared<Fix42::Message>();
    message->setType(Fix42::kMessageType::kQuote);
    message->setField<Fix42::kFieldName::kSymbol>(symbol);
    message->setField<Fix42::kFieldName::kBidPx>(buy_quote.price);
    message->setField<Fix42::kFieldName::kBidSize>(buy_quote.quantity);
    message->setField<Fix42::kFieldName::kOfferPx>(sell_quote.price);
    message->setField<Fix42::kFieldName::kOfferSize>(sell_quote.quantity);
    results.push_back(message);
}
