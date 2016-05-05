#ifndef EXCHANGESIMULATOR_SERVER_TRADERECORD_H
#define EXCHANGESIMULATOR_SERVER_TRADERECORD_H

struct TradeRecord{
    int order_buy, order_sell, price, quantity;
    /* TimeStamp time */
};

#endif //EXCHANGESIMULATOR_SERVER_TRADERECORD_H
