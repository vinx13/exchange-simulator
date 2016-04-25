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

    while (!parser_.isDone()) {
        tag = parser_.goNextTag();
        if (kFieldType::kRepeatGroup == FieldTypeMap::get(tag)) {
            auto repeat_group = std::make_shared<RepeatGroup>();
            auto &repeat_units = repeat_group->getGroups();

            //repeat_groups_->set(tag, repeat_group);
            auto count_field = parser_.goNextFieldValue(kFieldType::kRepeatGroup);
            int count = std::static_pointer_cast<IntFieldValue>(count_field)->getValue(); //number of repeating units

            while (count-- > 0) {
                auto repeat_unit = std::make_shared<FieldValueContainer>();
                Tag subtag = parser_.goNextTag();
                Tag last_tag = -1;

                while (last_tag < subtag) {
                    auto field_value = parser_.goNextFieldValue(FieldTypeMap::get(subtag));
                    repeat_unit->set(subtag, field_value);
                    last_tag = subtag;
                    subtag = parser_.goNextTag();
                }
                parser_.goLastStart();
                repeat_units.push_back(repeat_unit);
            }

            repeat_groups_.set(tag, repeat_group);

        } else if (kFieldType::kLength == FieldTypeMap::get(tag)) {
            //TODO
        } else {
            auto field_value = parser_.goNextFieldValue(FieldTypeMap::get(tag));
            field_values_.set(tag, field_value);
        }
    }
}

__FIX42_END