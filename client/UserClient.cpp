#include <iostream>
#include <sstream>
#include "UserClient.h"

UserClient::UserClient(const std::string &config) : Client(config) {
}

void UserClient::start() {
    readClientName();
    connect();
    doMainLoop();
}

void UserClient::doMainLoop() {
    printUsage();
    while (true) {
        std::string cmd;
        std::getline(std::cin, cmd);
        if (!isvalid(cmd)) {
            std::cout << "Invalid command." << std::endl;
            printUsage();
        } else {
            handleCmd(cmd);
        }
    }
}

void UserClient::handleCmd(const std::string &cmd) {
    Fix42::MessagePtr message;
    std::string cmdbody = getCmdBody(cmd);
    switch (cmd[1]) {
        case 'l': {
            onQueryList();
            break;
        }
        case 'q': {
            onQueryQuote(cmdbody);
            break;
        }
        case 'b': {
            onBuy(cmdbody);
            break;
        }
        case 's': {
            onSell(cmdbody);
            break;
        }
        case 'o': {
            onQueryOrder(cmdbody);
            break;
        }
    }
}


void UserClient::readClientName() {
    std::cout << "Enter client name:";
    std::getline(std::cin, client_);
}

void UserClient::printUsage() const {
    const char *usage =
            "Usage:\n"\
            ":l                                     -- query the list of securities\n"\
            ":q symbol                              -- request quotes of specified security\n"\
            ":b symbol order_id price quantity      -- send buy order\n"\
            ":s symbol order_id price quantity    -- send sell order\n"\
            ":o order_id                            -- query order status\n";
    std::cout << usage << std::endl;

}

bool UserClient::isvalid(const std::string &cmd) {
    const std::vector<std::string> known_cmds = {":l", ":q", ":b", ":s", ":o"};
    for (auto &prefix:known_cmds) {
        if (cmd.find(prefix) == 0) {
            return true;
        }
    }
    return false;

}

void UserClient::onQueryQuote(const std::string &cmdbody) {
    auto message = std::make_shared<Fix42::Message>();
    message->setType(Fix42::kMessageType::kQuoteRequest);
    std::istringstream s(cmdbody);
    std::string symbol;

    if (!(s >> symbol)) {
        return;
    }

    auto requests = std::make_shared<Fix42::RepeatGroup>();
    auto unit = std::make_shared<Fix42::FieldValueContainer>(); //currently only one requests can be sent in a single message

    unit->setField<Fix42::kFieldName::kSymbol>(symbol);
    requests->addUnit(unit);
    message->setRepeatGroup(Fix42::kFieldName::kNoRelatedSym, requests);

    send(message);
    auto response = read();

    auto &quote_list = response->getRepeatGroup(Fix42::kFieldName::kNoRelatedSym)->getUnits();

    if (quote_list.empty()) {
        std::cout << "No available quotes." << std::endl;
        return;
    }
    for (auto &quote_fields: quote_list) {
        std::cout
            << "price -- " << quote_fields->getField<Fix42::kFieldName::kPrice>()->getValue()
            << "    side -- " << quote_fields->getField<Fix42::kFieldName::kSide>()->getValue()
            << "    quantity -- " << quote_fields->getField<Fix42::kFieldName::kOrderQty>()->getValue()
            << std::endl;
    }
}

void UserClient::onBuy(const std::string &cmdbody) {
    auto message = generateOrder(cmdbody);
    message->setField<Fix42::kFieldName::kSide>('b');

    send(message);
    auto response = read();

    std::cout << (isOrderAccepted(response) ? "Order accepted." : "Order rejected.") << std::endl;

}

void UserClient::onSell(const std::string &cmdbody) {
    auto message = generateOrder(cmdbody);
    message->setField<Fix42::kFieldName::kSide>('s');

    send(message);
    auto response = read();

    std::cout << (isOrderAccepted(response) ? "Order accepted." : "Order rejected.") << std::endl;
}

Fix42::MessagePtr UserClient::generateOrder(const std::string &cmdbody) {
    auto message = std::make_shared<Fix42::Message>();
    message->setType(Fix42::kMessageType::kNewOrderSingle);
    std::istringstream s(cmdbody);
    std::string symbol, client_order_id;
    double price, quantity;
    s >> symbol >> client_order_id >> price >> quantity;
    message->setField<Fix42::kFieldName::kClientID>(client_);
    message->setField<Fix42::kFieldName::kSymbol>(symbol);
    message->setField<Fix42::kFieldName::kClOrdID>(client_order_id);
    message->setField<Fix42::kFieldName::kPrice>(price);
    message->setField<Fix42::kFieldName::kOrderQty>(quantity);
    return message;
}

void UserClient::onQueryOrder(const std::string &cmdbody) {
    auto message = std::make_shared<Fix42::Message>();
    std::istringstream s(cmdbody);
    std::string client_order_id;
    if(!(s >> client_order_id))
        return;

    message->setType(Fix42::kMessageType::kOrderStatusRequest);
    message->setField<Fix42::kFieldName::kClientID>(client_);
    message->setField<Fix42::kFieldName::kClOrdID>(client_order_id);

    send(message);
    auto response = read();

    std::cout << "symbol    price    side   quantity   excuted quantity"  << std::endl;
    if(response->contains(Fix42::kFieldName::kSymbol)) {
        std::cout << response->getField<Fix42::kFieldName::kSymbol>()->getValue() << "       "
        << response->getField<Fix42::kFieldName::kPrice>()->getValue() << "        "
        << static_cast<char>(response->getField<Fix42::kFieldName::kSide>()->getValue()) << "      "
        << response->getField<Fix42::kFieldName::kOrderQty>()->getValue() << "      "
        << response->getField<Fix42::kFieldName::kCumQty>()->getValue() << "    "
        << std::endl;
    } else{
        std::cout << "Order not found" << std::endl;
    }
}

void UserClient::onQueryList() {
    auto message = std::make_shared<Fix42::Message>();
    message->setType(Fix42::kMessageType::kSecurityDefinitionRequest);

    send(message);
    auto response = read();

    auto security_list = response->getRepeatGroup(Fix42::kFieldName::kNoRelatedSym)->getUnits();
    std::cout << "symbol        price" << std::endl;

    if (security_list.empty()) {
        std::cout << "No available securities." << std::endl;
        return;
    }
    for (const auto &security_fields : security_list) {
        std::cout << security_fields->getField<Fix42::kFieldName::kSymbol>()->getValue() << "    "
        << security_fields->getField<Fix42::kFieldName::kPrice>()->getValue() << std::endl;
    }
}

bool UserClient::isOrderAccepted(Fix42::MessagePtr message) {
    return message->getField<Fix42::kFieldName::kOrdStatus>()->getValue() == 0;
}
