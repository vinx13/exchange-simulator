#include "FieldValue.h"

__FIX42_BEGIN

FieldValuePtr FieldValue::fromString(const kFieldType type, const std::string &s) {
    return FieldValue::fromString(type, s.cbegin(), s.cend());
}

FieldValuePtr FieldValue::fromString(const kFieldType type,
                                     std::string::const_iterator begin,
                                     std::string::const_iterator end) {
    switch (type) {
        case kChar:
            return std::make_shared<CharFieldValue>(*begin);
        case kInt: case kRepeatGroup:
            return std::make_shared<IntFieldValue>(std::stoi(std::string(begin, end)));
        case kFloat:
            return std::make_shared<FloatFieldValue>(std::stod(std::string(begin, end)));
        case kString:
            return std::make_shared<StringFieldValue>(begin, end);
        case kData:
            return std::make_shared<DataFieldValue>(begin, end);
        default:
            throw BadFieldType();
    }
}


std::string CharFieldValue::toString() const {
    return std::string(1, value_) + DELIMITER;
}

std::string StringFieldValue::toString() const {
    return value_ + DELIMITER;
}


std::string DataFieldValue::toString() const {
    return std::string(value_, value_ + len_) + DELIMITER;
}

std::string FloatFieldValue::toString() const {
    return std::to_string(value_) + DELIMITER;
}

std::string IntFieldValue::toString() const {
    return std::to_string(value_) + DELIMITER;
}

__FIX42_END