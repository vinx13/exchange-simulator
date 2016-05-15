#include "SecurityDefHandler.h"

std::vector<Fix42::MessagePtr> SecurityDefHandler::accept(const Fix42::MessagePtr message) {
    std::vector<Fix42::MessagePtr> results;
    auto result = std::make_shared<Fix42::Message>();
    auto requests = message->getRepeatGroup(Fix42::kFieldName::kNoRelatedSym)->getUnits();

    result->setType(Fix42::kMessageType::kSecurityDefinition);
    std::vector<SecurityStatus> securities;
    api_.securityQueryAll(securities);
    for(const auto &security:securities){

    }
    return results;
}