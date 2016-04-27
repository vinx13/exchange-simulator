#include "gtest/gtest.h"
#include "Fix42.h"
#include "util.h"

TEST(TestFieldGroup, ToString) {
    Fix42::RepeatGroup group;
    auto &units = group.getGroups();
    auto unit = std::make_shared<Fix42::FieldValueContainer>();
    unit->set(8, fromValue<Fix42::kFieldType::kString>("123"));
    unit->set(9, fromValue<Fix42::kFieldType::kInt>(12));
    units.push_back(unit);
    unit = std::make_shared<Fix42::FieldValueContainer>();
    unit->set(11, fromValue<Fix42::kFieldType::kChar>('a'));
    unit->set(10, fromValue<Fix42::kFieldType::kFloat>(1.5));
    units.push_back(unit);

    std::string expect("2\0018=123\0019=12\00110=");
    expect += std::to_string(1.5) + "\00111=a\001";
    EXPECT_EQ(expect, group.toString());
}
