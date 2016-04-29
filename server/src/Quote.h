#ifndef EXCHANGESIMULATOR_SERVER_QUOTE_H
#define EXCHANGESIMULATOR_SERVER_QUOTE_H


#include "Fix42.h"

enum class kTradeSide :char{
    kBuy, kSell
};

struct Quote {
    int id = -1; //assigned by system
    std::string symbol, client, client_order_id;
    int price, quantity;
    kTradeSide side;

    Quote(const Fix42::MessagePtr message) {
        symbol = message->getField<Fix42::kFieldName::kSymbol>()->getValue();
        client = message->getField<Fix42::kFieldName::kClientID>()->getValue();
        client_order_id = message->getField<Fix42::kFieldName::kClOrdID>()->getValue();
        side = static_cast<kTradeSide>(message->getField<Fix42::kFieldName::kSide>()->getValue());
        quantity = message->getField<Fix42::kFieldName::kOrderQty>()->getValue();
        //stores it as an integer to avoid precision loss with floating number
        price = message->getField<Fix42::kFieldName::kPrice>()->getValue() * 100;
    }

};


#endif //EXCHANGESIMULATOR_SERVER_QUOTE_H
