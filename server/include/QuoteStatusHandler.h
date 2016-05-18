#ifndef EXCHANGESIMULATOR_SERVER_QUOTESTATUSHANDLER_H
#define EXCHANGESIMULATOR_SERVER_QUOTESTATUSHANDLER_H

#include "MessageHandler.h"

class QuoteStatusHandler : public MessageHandler {
public:
    QuoteStatusHandler(APIUtil::ConnPtr conn) : MessageHandler(conn) { }

    virtual std::vector<Fix42::MessagePtr> accept(const Fix42::MessagePtr message) override;
};


#endif //EXCHANGESIMULATOR_SERVER_QUOTESTATUSHANDLER_H
