#include "gtest/gtest.h"
#include "Fix42.h"
#include "util.h"

TEST(TestMessage, Parser) {
    std::string s("8=FIX4.2\0019=50\00135=A\001");
    Fix42::Message message(s);
    EXPECT_EQ(std::string("FIX4.2"),message.getField<Fix42::kFieldName::kBeginString>()->getValue());
    EXPECT_EQ(50, message.getField<Fix42::kFieldName::kBodyLength>()->getValue());
    EXPECT_EQ('A', message.getField<Fix42::kFieldName::kMsgType>()->getValue()[0]);
    EXPECT_EQ(static_cast<Fix42::kMessageType>('A'), message.getType());
}

TEST(TestMessage, MessageType){
    Fix42::Message message;
    auto type = Fix42::kMessageType::kAdvertisement;
    message.setType(type);
    EXPECT_EQ(type, message.getType());
}

