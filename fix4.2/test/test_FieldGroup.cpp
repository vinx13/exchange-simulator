#include "gtest/gtest.h"
#include "fix4.2/Fix42.h"
#include "util.h"

TEST(TestFieldGroup, Set) {
    Fix42::FieldGroup group;
    group.set(1, fromValue<Fix42::kFieldType::kInt>(1));
    EXPECT_EQ(1, std::static_pointer_cast<Fix42::IntFieldValue>(group.get(1))->getValue());
}


TEST(TestFieldGroup, Contain) {
    Fix42::FieldGroup group;
    group.set(1, fromValue<Fix42::kFieldType::kInt>(1));
    EXPECT_TRUE(group.contains(1));
}

TEST(TestFieldGroup, NoOverride) {
    Fix42::FieldGroup group;
    group.set(1, fromValue<Fix42::kFieldType::Int>(1));
    EXPECT_NO_THROW(group.set(1, fromValue<Fix42::kFieldType::Int>(2)));
}
