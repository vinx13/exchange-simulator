#include "FieldGroup.h"


__FIX42_BEGIN

const FieldValuePtr FieldGroup::get(Tag tag) const noexcept {
    auto it = fields_.find(tag);

    return (it != fields_.cend()) ?
           it->second : FieldValuePtr();
}

void FieldGroup::set(Tag tag, FieldValuePtr value, bool override) throw(DuplicateTag) {
    if (override || fields_.find(tag) == fields_.end()) {
        //override or key does not exist
        fields_[tag] = value;
        return;
    }
    throw DuplicateTag();
}

bool FieldGroup::contains(Tag tag) const noexcept {
    return fields_.find(tag) != fields_.cend();
}

std::string FieldGroup::toString() const noexcept {
    std::string result;
    for(auto field: fields_){
        result+=std::to_string(field.first) + '=' + field.second->toString() + DELIMITER;
    }
    return result;
}

__FIX42_END