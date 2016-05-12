#include "SecurityStatusHandler.h"


std::vector<Fix42::MessagePtr> SecurityStatusHandler::accept(const Fix42::MessagePtr message) {
    std::vector<Fix42::MessagePtr> results;
    const auto &symbol = message->getField<Fix42::kFieldName::kSymbol>()->getValue();
    const auto &status = static_cast<kSecurityTradingStatus>(
            message->getField<Fix42::kFieldName::kSecurityTradingStatus>()->getValue()
    );
    api_.securityUpdateTradingStatus(symbol, status);
    return std::vector<Fix42::MessagePtr>();
}