#ifndef EXCHANGESIMULATOR_SERVER_MESSAGEPROCESSOR_H
#define EXCHANGESIMULATOR_SERVER_MESSAGEPROCESSOR_H


#include "Fix42.h"
#include "ConnectionFactory.h"

#include <memory>

class MessageProcessor {
public:
    MessageProcessor(ConnectionFactory::ConnectionPtr dbconn) : dbconn_(dbconn) { }

    Fix42::MessagePtr accept(const Fix42::MessagePtr message);

protected:
    Fix42::MessagePtr processSingleOrder(const Fix42::MessagePtr message);

    ConnectionFactory::ConnectionPtr dbconn_;
};


#endif //EXCHANGESIMULATOR_SERVER_MESSAGEPROCESSOR_H
