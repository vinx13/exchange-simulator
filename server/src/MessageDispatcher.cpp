#include "MessageDispatcher.h"
#include "OrderBook.h"
#include "Logger.h"
#include "OrderHandler.h"
#include "QuoteRequestHandler.h"
#include "SecurityStatusHandler.h"
#include "SecurityDefinitionHandler"

#include <sstream>

const std::string MessageDispatcher::TAG("MessageDispatcher");

std::vector<Fix42::MessagePtr> MessageDispatcher::dispatch(const Fix42::MessagePtr message) {

    auto type = message->getType();

    if (handler_map_.find(type) != handler_map_.end()) {
        return handler_map_.at(type)->accept(message);
    }

    logUnknown(type);
    return std::vector<Fix42::MessagePtr>();
}

void MessageDispatcher::logUnknown(const Fix42::kMessageType &type) const {
    std::ostringstream error_msg;
    error_msg << "unknown message type '" << static_cast<char>(type) + '\'';
    Logger::getLogger()->error(TAG, error_msg.str());
}

void MessageDispatcher::initHandlerMap() {
#define DECLARE_HANDLER_MAP(MESSAGE_TYPE, HANDLER_TYPE) \
    do{ \
        handler_map_[Fix42::kMessageType::MESSAGE_TYPE] = std::make_shared<HANDLER_TYPE>(dbconn_); \
    } while(0);


    DECLARE_HANDLER_MAP(kNewOrderList, OrderHandler)
    DECLARE_HANDLER_MAP(kNewOrderSingle, OrderHandler)
    DECLARE_HANDLER_MAP(kQuoteRequest, QuoteRequestHandler)
    DECLARE_HANDLER_MAP(kOrderStatusRequest, OrderHandler)
    DECLARE_HANDLER_MAP(kSecurityStatus, SecurityStatusHandler)
    DECLARE_HANDLER_MAP(kSecurityDefinitionRequest, SecurityDefinitionHandler)

#undef DECLARE_HANDLER_MAP
}