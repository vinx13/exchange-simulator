#include "Message.h"
#include "FieldTypeMap.h"
#include <algorithm>

__FIX42_BEGIN

Message::Message(std::string s) : parser_(s.begin(), s.end()) {
    parse();
}

Message::Message(std::string::iterator begin, std::string::iterator end) : parser_(begin, end) {
    parse();
}

void Message::parse() {
    Tag tag;
    auto type_map = FieldTypeMap::getInstance();

    while (!parser_.isDone()) {
        tag = parser_.goNextTag();
        if (kFieldType::kRepeatGroup == type_map->get(tag)) {

            auto repeat_group = std::make_shared<RepeatGroup>();
            auto &group_container = repeat_group->getGroups();

            auto count_field = parser_.goNextFieldValue(kFieldType::kRepeatGroup);
            int count = std::static_pointer_cast<IntFieldValue>(count_field)->getValue();

            while (count-- > 0) {
                Tag t = parser_.goNextTag();
                auto field_value = parser_.goNextFieldValue(type_map->get(t));
                group_container.set(t, field_value);
            }
            repeat_groups_.set(tag,repeat_group);

        } else {
            auto field_value = parser_.goNextFieldValue(type_map->get(tag));
            field_values_.set(tag, field_value);
        }
    }
}


__FIX42_END