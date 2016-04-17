#include "FieldGroup.h"

const std::shared_ptr<FieldValue *> FieldGroup::get(FieldGroup::Tag tag) const {
    auto it = fields_.find(tag);
    return it == fields_.end() ?
           std::shared_ptr<FieldValue *>() : it->second;
}

bool FieldGroup::set(Tag tag, std::shared_ptr<FieldValue *> value, bool override) {
    if (override || fields_.find(tag) == fields_.end()) {
        //override or key does not exist
        fields_[tag] = value;
        return true;
    }
    return false;
}
