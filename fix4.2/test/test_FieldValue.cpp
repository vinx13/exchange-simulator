#include "gtest/gtest.h"
#include "Fix42.h"
#include "util.h"

TEST(TestFieldValue, CharFieldValue) {
    EXPECT_EQ('a', fromString<Fix42::kFieldType::kChar>("a")->getValue());

    EXPECT_EQ("a\001", fromValue<Fix42::kFieldType::kChar>('a')->toString());
}

TEST(TestFieldValue, IntFieldValue) {
    EXPECT_EQ(123, fromString<Fix42::kFieldType::kInt>("123")->getValue());
    EXPECT_NE(123, fromString<Fix42::kFieldType::kInt>("1234")->getValue());
    EXPECT_EQ(-123, fromString<Fix42::kFieldType::kInt>("-123")->getValue());

    EXPECT_EQ("123\001", fromValue<Fix42::kFieldType::kInt>(123)->toString());
}

TEST(TestFieldValue, FloatFieldValue) {
    EXPECT_DOUBLE_EQ(0.1, fromString<Fix42::kFieldType::kFloat>("0.10")->getValue());
    EXPECT_DOUBLE_EQ(0.1, fromString<Fix42::kFieldType::kFloat>("0.1")->getValue());
    EXPECT_DOUBLE_EQ(-0.1, fromString<Fix42::kFieldType::kFloat>("-0.1")->getValue());
    EXPECT_DOUBLE_EQ(1, fromString<Fix42::kFieldType::kFloat>("1")->getValue());
    EXPECT_DOUBLE_EQ(1, fromString<Fix42::kFieldType::kFloat>("1.0")->getValue());
}

TEST(TestFieldValue, StringFieldValue) {
    EXPECT_EQ(std::string("abc"), fromString<Fix42::kFieldType::kString>("abc")->getValue());

    EXPECT_EQ("abc\001", fromValue<Fix42::kFieldType::kString>("abc")->toString());
}

TEST(TestFieldValue, DataFieldValue) {
    char src[] = "0123456789";
    auto data = fromString<Fix42::kFieldType::kData>(src);
    EXPECT_EQ(10, data->getLength());
    const char *begin = data->getValue();
    for (int i = 0; i < data->getLength(); i++) {
        EXPECT_EQ(src[i], begin[i]);
    }

    auto expect = std::string(src) + '\001';
    EXPECT_EQ(expect, fromValue<Fix42::kFieldType::kData>(src, 10)->toString());
    EXPECT_EQ(expect, data->toString());
}



