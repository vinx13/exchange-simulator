#include "gtest/gtest.h"
#include "fix4.2/Fix42.h"

template<Fix42::kFieldType FIELD_TYPE>
std::shared_ptr<
        typename Fix42::FieldValueType<FIELD_TYPE>::Type>
static createFieldValue(const char *s) {
    return std::static_pointer_cast<
            typename Fix42::FieldValueType<FIELD_TYPE>::Type>(
            Fix42::FieldValue::fromString(FIELD_TYPE, std::string(s))
    );
}


TEST(TestFieldValue, CharFieldValue) {
    EXPECT_EQ('a', createFieldValue<Fix42::kFieldType::Char>("a")->getValue());

}

TEST(TestFieldValue, IntFieldValue) {
    EXPECT_EQ(123, createFieldValue<Fix42::kFieldType::Int>("123")->getValue());
    EXPECT_NE(123, createFieldValue<Fix42::kFieldType::Int>("1234")->getValue());
    EXPECT_EQ(-123, createFieldValue<Fix42::kFieldType::Int>("-123")->getValue());
}

TEST(TestFieldValue, FloatFieldValue) {
    EXPECT_DOUBLE_EQ(0.1, createFieldValue<Fix42::kFieldType::Float>("0.10")->getValue());
    EXPECT_DOUBLE_EQ(0.1, createFieldValue<Fix42::kFieldType::Float>("0.1")->getValue());
    EXPECT_DOUBLE_EQ(-0.1, createFieldValue<Fix42::kFieldType::Float>("-0.1")->getValue());
    EXPECT_DOUBLE_EQ(1, createFieldValue<Fix42::kFieldType::Float>("1")->getValue());
    EXPECT_DOUBLE_EQ(1, createFieldValue<Fix42::kFieldType::Float>("1.0")->getValue());
}

TEST(TestFieldValue, StringFieldValue) {
    EXPECT_EQ(std::string("abc"),createFieldValue<Fix42::kFieldType::String>("abc")->getValue());
}

TEST(TestFieldValue, DataFieldValue) {
    char src[]="0123456789\001";
    auto data = createFieldValue<Fix42::kFieldType::Data>(src);
    EXPECT_EQ(11,data->getLength());
    const char *begin = data->getValue();
    for(int i = 0; i < data->getLength(); i++){
        EXPECT_EQ(src[i], begin[i]);
    }
}



