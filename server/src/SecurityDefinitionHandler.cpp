#include "SecurityDefinitionHandler"

std::vector<Fix42::MessagePtr> SecurityDefinitionHandler::accept(const Fix42::MessagePtr message) {
    std::vector<Fix42::MessagePtr> results;
    auto result = std::make_shared<Fix42::Message>();
    //auto requests = message->getRepeatGroup(Fix42::kFieldName::kNoRelatedSym)->getUnits();

    result->setType(Fix42::kMessageType::kSecurityDefinition);
    std::vector<SecurityStatus> securities;
    api_.securityQueryAll(securities);

    auto security_list = std::make_shared<Fix42::RepeatGroup>();

    for (const auto &security:securities) {
        auto unit = std::make_shared<Fix42::FieldValueContainer>();
        unit->setField<Fix42::kFieldName::kSymbol>(security.symbol);
        unit->setField<Fix42::kFieldName::kPrice>(Quote::toOriginalPrice(security.price));
        security_list->addUnit(unit);
    }

    result->setRepeatGroup(Fix42::kFieldName::kNoRelatedSym, security_list);
    results.push_back(result);
    return results;
}
