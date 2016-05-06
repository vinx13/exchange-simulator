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