#include "FieldValue.h"

__FIX42_BEGIN

FieldValuePtr FieldValue::fromString(const kFieldType type, const std::string &s) {
    return FieldValue::fromString(type, s.cbegin(), s.cend());
}

FieldValuePtr FieldValue::fromString(const kFieldType type,
                                     std::string::const_iterator begin,
                                     std::string::const_iterator end) {
    switch (type) {
        case kFieldType::kChar:
            return std::make_shared<CharFieldValue>(*begin);
        case kFieldType::kInt: case kFieldType::kRepeatGroup:
            return std::make_shared<IntFieldValue>(std::stoi(std::string(begin, end)));
        case kFieldType::kFloat:
            return std::make_shared<FloatFieldValue>(std::stod(std::string(begin, end)));
        case kFieldType::kLength:
            return std::make_shared<LengthFieldValue>(std::stoul(std::string(begin, end)));
        case kFieldType::kString:
            return std::make_shared<StringFieldValue>(begin, end);
        case kFieldType::kData:
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

std::string LengthFieldValue::toString() const {
    return std::to_string(value_) + DELIMITER;
}

__FIX42_END