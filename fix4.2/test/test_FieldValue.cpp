#include "gtest/gtest.h"
#include "fix4.2/Fix42.h"

/* create smart pointer to FieldValue from string */
template<Fix42::kFieldType FIELD_TYPE>
static std::shared_ptr<
        typename Fix42::FieldValueType<FIELD_TYPE>::Type>
fromString(const char *s) {
    return std::static_pointer_cast<
            typename Fix42::FieldValueType<FIELD_TYPE>::Type>(
            Fix42::FieldValue::fromString(FIELD_TYPE, std::string(s))
    );
}

/* create smarter pointer to FieldValue from its constructor directly */
template<Fix42::kFieldType FIELD_TYPE, class ...Arg>
static std::shared_ptr<
        typename Fix42::FieldValueType<FIELD_TYPE>::Type>
fromValue(Arg ...arg) {
    return std::make_shared<typename Fix42::FieldValueType<FIELD_TYPE>::Type>(std::forward<Arg>(arg)...);
};

TEST(TestFieldValue, CharFieldValue) {
    EXPECT_EQ('a', fromString<Fix42::kFieldType::Char>("a")->getValue());

    EXPECT_EQ("a\001", fromValue<Fix42::kFieldType::Char>('a')->toString());
}

TEST(TestFieldValue, IntFieldValue) {
    EXPECT_EQ(123, fromString<Fix42::kFieldType::Int>("123")->getValue());
    EXPECT_NE(123, fromString<Fix42::kFieldType::Int>("1234")->getValue());
    EXPECT_EQ(-123, fromString<Fix42::kFieldType::Int>("-123")->getValue());

    EXPECT_EQ("123\001", fromValue<Fix42::kFieldType::Int>(123)->toString());
}

TEST(TestFieldValue, FloatFieldValue) {
    EXPECT_DOUBLE_EQ(0.1, fromString<Fix42::kFieldType::Float>("0.10")->getValue());
    EXPECT_DOUBLE_EQ(0.1, fromString<Fix42::kFieldType::Float>("0.1")->getValue());
    EXPECT_DOUBLE_EQ(-0.1, fromString<Fix42::kFieldType::Float>("-0.1")->getValue());
    EXPECT_DOUBLE_EQ(1, fromString<Fix42::kFieldType::Float>("1")->getValue());
    EXPECT_DOUBLE_EQ(1, fromString<Fix42::kFieldType::Float>("1.0")->getValue());
}

TEST(TestFieldValue, StringFieldValue) {
    EXPECT_EQ(std::string("abc"), fromString<Fix42::kFieldType::String>("abc")->getValue());

    EXPECT_EQ("abc\001", fromValue<Fix42::kFieldType::String>("abc")->toString());
}

TEST(TestFieldValue, DataFieldValue) {
    char src[] = "0123456789";
    auto data = fromString<Fix42::kFieldType::Data>(src);
    EXPECT_EQ(10, data->getLength());
    const char *begin = data->getValue();
    for (int i = 0; i < data->getLength(); i++) {
        EXPECT_EQ(src[i], begin[i]);
    }

    auto expect = std::string(src)+'\001';
    EXPECT_EQ(expect, fromValue<Fix42::kFieldType::Data>(src, 10)->toString());
    EXPECT_EQ(expect, data->toString());
}



