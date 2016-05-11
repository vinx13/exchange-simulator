#ifndef EXCHANGESIMULATOR_SERVER_MESSAGEDISPATCH_H
#define EXCHANGESIMULATOR_SERVER_MESSAGEDISPATCH_H


#include "Fix42.h"
#include "ConnectionFactory.h"
#include "MessageHandler.h"

#include <memory>
#include <string>
#include <map>
#include <vector>

class MessageDispatcher {
public:
    static const std::string TAG;

    void initHandlerMap();

    MessageDispatcher(ConnectionFactory::ConnectionPtr dbconn) : dbconn_(dbconn) { initHandlerMap(); }

    std::vector<Fix42::MessagePtr> dispatch(const Fix42::MessagePtr message);

private:
    std::map<Fix42::kMessageType, std::shared_ptr<MessageHandler>> handler_map_;

    ConnectionFactory::ConnectionPtr dbconn_;

    void logUnknown(const Fix42::kMessageType &type) const;
};


#endif //EXCHANGESIMULATOR_SERVER_MESSAGEDISPATCH_H
