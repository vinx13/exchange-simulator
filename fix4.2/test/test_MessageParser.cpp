#include "gtest/gtest.h"
#include "Fix42.h"
#include "MessageParser.h"
#include "util.h"


TEST(TestMessageParser, Basic) {
    std::string s("7=2\0018=ab\001");
    Fix42::MessageParser parser(s.begin(), s.end());
    EXPECT_FALSE(parser.isDone());
    EXPECT_EQ(7, parser.goNextTag());
    EXPECT_EQ(2,
              std::static_pointer_cast<Fix42::IntFieldValue>(
                      parser.goNextFieldValue(Fix42::kFieldType::kInt)
              )->getValue());
    EXPECT_FALSE(parser.isDone());
    EXPECT_EQ(8, parser.goNextTag());
    EXPECT_EQ(std::string("ab"),
              std::static_pointer_cast<Fix42::StringFieldValue>(
                      parser.goNextFieldValue(Fix42::kFieldType::kString)
              )->getValue());
    EXPECT_TRUE(parser.isDone());
}
