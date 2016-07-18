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

        if(api_.orderBookQuery(symbol, kTradeSide::kBuy, true, quotes[0]))
            addToQuoteList(quote_list, quotes[0]);

        if(api_.orderBookQuery(symbol, kTradeSide::kSell, false, quotes[1]))
            addToQuoteList(quote_list, quotes[1]);
    }
    result->setRepeatGroup(Fix42::kFieldName::kNoRelatedSym, quote_list);
    results.push_back(result);
    return results;
}

void QuoteRequestHandler::addToQuoteList(std::shared_ptr<Fix42::RepeatGroup> &quote_list, const Quote &quote) const {
    auto quote_fields = std::make_shared<Fix42::FieldValueContainer>();
    quote_fields->setField<Fix42::kFieldName::kSymbol>(quote.symbol);
    quote_fields->setField<Fix42::kFieldName::kPrice>(Quote::toOriginalPrice(quote.price));
    quote_fields->setField<Fix42::kFieldName::kSide>(static_cast<char>(quote.side));
    quote_fields->setField<Fix42::kFieldName::kOrderQty>(quote.quantity);
    quote_list->addUnit(quote_fields);
}
