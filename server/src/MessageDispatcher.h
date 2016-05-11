#ifndef EXCHANGESIMULATOR_SERVER_MESSAGEHANDLER_H
#define EXCHANGESIMULATOR_SERVER_MESSAGEHANDLER_H


#include "Fix42.h"
#include "TradeRecord.h"
#include "ConnectionFactory.h"
#include "Quote.h"

#include <vector>
#include <memory>

class MessageDispatcher {
public:
    MessageDispatcher(ConnectionFactory::ConnectionPtr dbconn) : dbconn_(dbconn) { }

    Fix42::MessagePtr accept(const Fix42::MessagePtr message);

protected:
    Fix42::MessagePtr onSingleOrder(const Fix42::MessagePtr message);

    ConnectionFactory::ConnectionPtr dbconn_;

    Fix42::MessagePtr createMsgOrdAc(const Quote &quote);

    Fix42::MessagePtr createMsgOrdReject(const Quote &quote);

    void addBasicFields(const Quote &quote, std::shared_ptr<Fix42::Message> &message) const;
};


#endif //EXCHANGESIMULATOR_SERVER_MESSAGEHANDLER_H
