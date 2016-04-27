#include "gtest/gtest.h"
#include "Fix42.h"
#include "util.h"

TEST(TestFieldContainer, Set) {
    Fix42::FieldValueContainer container;
    container.set(1, fromValue<Fix42::kFieldType::kInt>(1));
    EXPECT_EQ(1, std::static_pointer_cast<Fix42::IntFieldValue>(container.get(1))->getValue());
}


TEST(TestFieldFieldContainer, Contains) {
    Fix42::FieldValueContainer container;
    container.set(1, fromValue<Fix42::kFieldType::kInt>(1));
    EXPECT_TRUE(container.contains(1));
}

TEST(TestFieldContainer, NoOverride) {
    Fix42::FieldValueContainer container;
    container.set(1, fromValue<Fix42::kFieldType::kInt>(1));
    EXPECT_NO_THROW(container.set(1, fromValue<Fix42::kFieldType::kInt>(2)));
}
