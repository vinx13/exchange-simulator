#include "MessageParser.h"


__FIX42_BEGIN

Tag MessageParser::goNextTag() {
    auto eq = std::find(current_, end_, '=');
    if (eq == end_) {
        throw BadTag();
    }
    Tag tag = std::stoi(std::string(current_, eq));
    current_ = eq;
    return tag;
}

void MessageParser::goLastStart() {
    while ((*current_) != DELIMITER) {
        if (current_ == begin_) {
            return;
        }
        --current_;
    }
    ++current_;
}

FieldValuePtr MessageParser::goNextFieldValue(kFieldType type, size_t len) {
    //Data field must specify len
    if (len != -1) {
        return FieldValue::fromString(type, current_, current_ + len);
    }
    auto soh = std::find(current_, end_, DELIMITER);
    if (soh == end_) {
        throw BadFieldValue();
    }
    return FieldValue::fromString(type, current_, end_);
}

bool MessageParser::isDone() const {
    return current_ == end_;
}

__FIX42_END