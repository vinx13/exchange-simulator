#ifndef EXCHANGESIMULATOR_SERVER_QUOTESTATUSHANDLER_H
#define EXCHANGESIMULATOR_QUOTESTATUSHANDLER_H


class QuoteStatusHandler {
    QuoteStatusHandler(APIUtil::ConnPtr conn) : MessageHandler(conn) { }

    virtual std::vector<Fix42::MessagePtr> accept(const Fix42::MessagePtr message) override;

};


#endif //EXCHANGESIMULATOR_QUOTESTATUSHANDLER_H
