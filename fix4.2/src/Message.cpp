#include "Message.h"
#include "FieldTypeMap.h"
#include <algorithm>
#include <sstream>

__FIX42_BEGIN

Message::Message() {

}

Message::Message(const std::string &s) {
    parse(s.begin(), s.end());
}

Message::Message(std::string::const_iterator begin, std::string::const_iterator end) {
    parse(begin, end);
}

void Message::parse(std::string::const_iterator begin, std::string::const_iterator end) {
    Tag tag;

    MessageParser parser(begin, end);

    while (!parser.isDone()) {
        tag = parser.goNextTag();

        if (kFieldType::kRepeatGroup == FieldTypeMap::get(tag)) {
            parseRepeatGroup(parser, tag);
        } else if (kFieldType::kLength == FieldTypeMap::get(tag)) {
            parseDataField(parser, tag);
        } else {
            parseGeneralField(parser, tag);
        }
    }
}

void Message::parseRepeatGroup(MessageParser &parser, const Tag tag) {
    auto repeat_group = std::make_shared<RepeatGroup>();
    auto &repeat_units = repeat_group->getGroups();

    //repeat_groups_->set(tag, repeat_group);
    auto count_field = parser.goNextFieldValue(kFieldType::kRepeatGroup);
    int count = std::static_pointer_cast<IntFieldValue>(count_field)->getValue(); //number of repeating units

    while (count-- > 0) {
        auto repeat_unit = std::make_shared<FieldValueContainer>();
        Tag subtag = parser.goNextTag();
        Tag last_tag = -1;

        while (last_tag < subtag) {
            auto field_value = parser.goNextFieldValue(FieldTypeMap::get(subtag));
            repeat_unit->set(subtag, field_value);
            last_tag = subtag;
            subtag = parser.goNextTag();
        }
        parser.goLastStart();
        repeat_units.push_back(repeat_unit);
    }

    repeat_groups_.set(tag, repeat_group);
}

void Message::parseDataField(MessageParser &parser, const Tag tag) {
    //TODO
}

void Message::parseGeneralField(MessageParser &parser, const Tag tag) {

    auto field_value = parser.goNextFieldValue(FieldTypeMap::get(tag));

    //filter special fields
    if (static_cast<Tag>(kFieldName::kBeginString) == tag) {
        setBeginString(
                std::static_pointer_cast<
                        typename FieldValueType<
                                FieldTypeMap::get(kFieldName::kMsgType)>::Type>(field_value)
                        ->getValue()
        );
        return;
    }
    if (static_cast<Tag>(kFieldName::kBodyLength) == tag) {
        setBodyLength(
                std::static_pointer_cast<
                        typename FieldValueType<
                                FieldTypeMap::get(kFieldName::kBodyLength)>::Type>(field_value)
                        ->getValue()
        );
        return;
    }
    field_values_.set(tag, field_value);
}

bool Message::contains(kFieldName name) {
    if (kFieldType::kRepeatGroup == FieldTypeMap::get(name))
        return repeat_groups_.contains(static_cast<Tag>(name));
    else
        return field_values_.contains(static_cast<Tag>(name));
}

kMessageType Message::getType() const {
    return static_cast<kMessageType>(getField<kFieldName::kMsgType>()->getValue()[0]);
}

void Message::setType(kMessageType type) {
    std::string type_str = std::string(1, static_cast<char>(type));
    auto value = std::make_shared<
            typename FieldValueType<
                    FieldTypeMap::get(kFieldName::kMsgType)>::Type>
            (type_str);

    field_values_.set(static_cast<Tag>(kFieldName::kMsgType), value, true);
}

int Message::getBodyLength() const {
    if (body_length_) {
        return body_length_;
    }
    std::string s = field_values_.toString() + repeat_groups_.toString();
    body_length_ = s.length();
    return body_length_;
}

std::string Message::toString() const {
    std::string result = field_values_.toString() + repeat_groups_.toString();
    body_length_ = result.length();
    std::ostringstream s;
    s << std::to_string(static_cast<Tag>(kFieldName::kBeginString))
    << '=' << begin_string_ << DELIMITER
    << std::to_string(static_cast<Tag>(kFieldName::kBodyLength))
    << '=' + std::to_string(body_length_) + DELIMITER;
    s << result;
    return s.str();
}

__FIX42_END