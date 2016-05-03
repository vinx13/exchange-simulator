#ifndef EXCHANGESIMULATOR_SERVER_MESSAGEHANDLER_H
#define EXCHANGESIMULATOR_SERVER_MESSAGEHANDLER_H


#include "Fix42.h"
#include "ConnectionFactory.h"

#include <memory>

class MessageHandler {
public:
    MessageHandler(ConnectionFactory::ConnectionPtr dbconn) : dbconn_(dbconn) { }

    Fix42::MessagePtr accept(const Fix42::MessagePtr message);

protected:
    Fix42::MessagePtr handleSingleOrder(const Fix42::MessagePtr message);

    ConnectionFactory::ConnectionPtr dbconn_;
};


#endif //EXCHANGESIMULATOR_SERVER_MESSAGEHANDLER_H
