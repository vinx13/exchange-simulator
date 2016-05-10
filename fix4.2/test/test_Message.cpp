#include "gtest/gtest.h"
#include "Fix42.h"
#include "util.h"

TEST(TestMessage, Parser) {
    std::string s("8=FIX4.2\0011=FIX\0017=50\00135=A\001");
    Fix42::Message message(s);
    EXPECT_EQ(std::string("FIX4.2"), message.getBeginString());
    EXPECT_EQ(std::string("FIX"), message.getField<Fix42::kFieldName::kAccount>()->getValue());
    EXPECT_EQ(50, message.getField<Fix42::kFieldName::kBeginSeqNo>()->getValue());
    EXPECT_EQ('A', message.getField<Fix42::kFieldName::kMsgType>()->getValue()[0]);
    EXPECT_EQ(static_cast<Fix42::kMessageType>('A'), message.getType());
}

TEST(TestMessage, MessageType) {
    Fix42::Message message;
    auto type = Fix42::kMessageType::kAdvertisement;
    message.setType(type);
    EXPECT_EQ(type, message.getType());
}

TEST(TestMessage, ToString) {
    Fix42::Message message;
    auto type = Fix42::kMessageType::kNewOrderSingle;
    message.setType(type);
    message.setBeginString("FIX.4.2");
    message.setField<Fix42::kFieldName::kSymbol>("symbol");
    message.setField<Fix42::kFieldName::kPrice>(100.0);

    std::string expect_body("35=D\00144=");
    expect_body += std::to_string(100.0);
    expect_body += "\00155=symbol\001";
    std::string expect("8=FIX.4.2\0019=");
    expect = expect + std::to_string(expect_body.length()) + '\001' + expect_body;
    EXPECT_EQ(expect, message.toString());
}

TEST(TestMessage, ToStringWithRepeatGroup) {
    Fix42::Message message;
    auto type = Fix42::kMessageType::kNewOrderList;
    message.setType(type);
    message.setBeginString("FIX.4.2");

    auto group = std::make_shared<Fix42::RepeatGroup>();

    auto unit = std::make_shared<Fix42::FieldValueContainer>();

    unit->setField<Fix42::kFieldName::kSymbol>("symbol1");
    unit->setField<Fix42::kFieldName::kPrice>(100.0);
    group->addUnit(unit);

    unit = std::make_shared<Fix42::FieldValueContainer>();
    unit->setField<Fix42::kFieldName::kSymbol>("symbol2");
    unit->setField<Fix42::kFieldName::kPrice>(200.0);
    group->addUnit(unit);

    message.setRepeatGroup(Fix42::kFieldName::kNoOrders, group);

    std::string expect("8=FIX.4.2\0019=");
    std::string expect_body("35=E\00173=2\00144=");
    expect_body += std::to_string(100.0);
    expect_body += "\00155=symbol1\00144=";
    expect_body += std::to_string(200.0);
    expect_body += "\00155=symbol2\001";
    expect = expect + std::to_string(expect_body.length()) + '\001' + expect_body;
    EXPECT_EQ(expect, message.toString());

}

TEST(TestMessage, ParserWithRepeatGroup) {
    std::string s("8=FIX.4.2\0019=");
    std::string s_body("35=E\00173=2\00144=");
    s_body += std::to_string(100.0);
    s_body += "\00155=symbol1\00144=";
    s_body += std::to_string(200.0);
    s_body += "\00155=symbol2\001";
    s = s + std::to_string(s_body.length()) + '\001' + s_body;

    Fix42::Message message(s);
    EXPECT_EQ(Fix42::kMessageType::kNewOrderList, message.getType());

    const auto orders = message.getRepeatGroup(Fix42::kFieldName::kNoOrders);
    EXPECT_EQ(2, orders->count());

    const auto units = orders->getUnits();
    const auto &first_order = units[0];
    const auto &second_order = units[1];

    EXPECT_EQ("symbol1", first_order->getField<Fix42::kFieldName::kSymbol>()->getValue());
    EXPECT_DOUBLE_EQ(100.0, first_order->getField<Fix42::kFieldName::kPrice>()->getValue());

    EXPECT_EQ("symbol2", second_order->getField<Fix42::kFieldName::kSymbol>()->getValue());
    EXPECT_DOUBLE_EQ(200.0, second_order->getField<Fix42::kFieldName::kPrice>()->getValue());
}