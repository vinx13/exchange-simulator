#ifndef EXCHANGESIMULATOR_SERVER_QUOTE_H
#define EXCHANGESIMULATOR_SERVER_QUOTE_H


#include "Fix42.h"
#include <cppconn/resultset.h>

enum class kTradeSide : char {
    kBuy = 'b', kSell = 's'
};

struct Quote {
    int id = -1; //assigned by system
    std::string symbol, client, client_order_id;
    int price, quantity;
    kTradeSide side;

    Quote(const Fix42::MessagePtr message) {
        fromContainer(message, *this);
    }

    Quote(const Fix42::FieldValueContainerPtr fields) {
        fromContainer(fields, *this);
    }

    Quote(std::shared_ptr<sql::ResultSet> res) {
        id = res->getInt("id");
        symbol = res->getString("symbol");
        client = res->getString("client");
        client_order_id = res->getString("client_order_id");
        price = res->getInt("price");
        quantity = res->getInt("quantity");
        side = static_cast<kTradeSide>(res->getString("side")[0]);
    }

    static int toIntPrice(double original) { return original * 100; }

    static double toOriginalPrice(int intPrice) { return intPrice / 100.0; }

private:
    template<class Container>
    static void fromContainer(const std::shared_ptr<Container> container, Quote &dest) {
        dest.symbol = container->template getField<Fix42::kFieldName::kSymbol>()->getValue();
        dest.client = container->template getField<Fix42::kFieldName::kClientID>()->getValue();
        dest.client_order_id = container->template getField<Fix42::kFieldName::kClOrdID>()->getValue();
        dest.side = static_cast<kTradeSide>(container->template getField<Fix42::kFieldName::kSide>()->getValue());
        dest.quantity = container->template getField<Fix42::kFieldName::kOrderQty>()->getValue();
        //stores it as an integer to avoid precision loss with floating number
        dest.price = toIntPrice(container->template getField<Fix42::kFieldName::kPrice>()->getValue());
    }
};


#endif //EXCHANGESIMULATOR_SERVER_QUOTE_H
