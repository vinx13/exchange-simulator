#include "QuoteRequestHandler.h"

std::vector<Fix42::MessagePtr> QuoteRequestHandler::accept(const Fix42::MessagePtr message) {
    std::vector<Fix42::MessagePtr> results;
    auto result = std::make_shared<Fix42::Message>();

    result->setType(Fix42::kMessageType::kQuote);

    auto requests = message->getRepeatGroup(Fix42::kFieldName::kNoRelatedSym)->getUnits();

    auto quote_list = std::make_shared<Fix42::RepeatGroup>();

    for (auto &request:requests) {
        std::string symbol = request->getField<Fix42::kFieldName::kSymbol>()->getValue();
        Quote quotes[2]; //0->buy, 1->sell
        bool success = true;
        success &= api_.orderBookQuery(symbol, kTradeSide::kBuy, false, quotes[0]);
        success &= api_.orderBookQuery(symbol, kTradeSide::kSell, true, quotes[1]);
        if (!success) {
            continue;
        }
        for (const auto &quote :quotes) {
            auto quote_fields = std::make_shared<Fix42::FieldValueContainer>();
            quote_fields->setField<Fix42::kFieldName::kSymbol>(quote.symbol);
            quote_fields->setField<Fix42::kFieldName::kSide>(static_cast<char>(quote.side));
            quote_fields->setField<Fix42::kFieldName::kOrderQty>(quote.quantity);
            quote_list->addUnit(quote_fields);
        }
    }
    result->setRepeatGroup(Fix42::kFieldName::kNoRelatedSym, quote_list);
    return results;
}
