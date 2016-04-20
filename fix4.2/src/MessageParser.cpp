#include "MessageParser.h"

__FIX42_BEGIN

Tag MessageParser::goNextTag() {
    auto eq = std::find(begin_, end_, '=');
    if (eq == end_) {
        throw BadTag();
    }
    Tag tag = std::stoi(std::string(begin_, eq));
    begin_ = eq;
    return tag;
}

FieldValuePtr MessageParser::goNextFieldValue(kFieldType type, size_t len) {
    //Data field must specify len
    if(len != -1){
        return FieldValue::fromString(type, begin_, begin_ + len);
    }
    auto soh  = std::find(begin_, end_, '\001');
    if(soh == end_) {
        throw BadFieldValue();
    }
    return FieldValue::fromString(type, begin_, end_);
}

__FIX42_END