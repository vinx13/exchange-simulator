#include "MessageDispatcher.h"
#include "OrderHandler.h"
#include "Logger.h"

#include <sstream>

const std::string MessageDispatcher::TAG("MessageDispatcher");

Fix42::MessagePtr MessageDispatcher::dispatch(const Fix42::MessagePtr message) {

    auto type = message->getType();

    if (handler_map_.find(type) != handler_map_.end()) {
        return handler_map_.at(type)->accept(message);
    }

    logUnknown(type);
    return Fix42::MessagePtr();
}

void MessageDispatcher::logUnknown(const Fix42::kMessageType &type) const {
    std::ostringstream error_msg;
    error_msg << "unknown message type '" << static_cast<char>(type) + '\'';
    Logger::getLogger()->error(TAG, error_msg.str());
}

void MessageDispatcher::initHandlerMap() {
    auto order_handler = std::make_shared<OrderHandler>(dbconn_);
    handler_map_[Fix42::kMessageType::kNewOrderSingle] = order_handler;
    handler_map_[Fix42::kMessageType::kNewOrderList] = order_handler;
}