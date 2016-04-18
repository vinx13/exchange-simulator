#include "RepeatGroup.h"

__FIX42_BEGIN

std::string Fix42::RepeatGroup::toString() const{
    std::string result = std::to_string(fields_.size()) + DELIMITER;
    for(auto field_group: fields_)
        result += field_group->toString();
    return result;
}

__FIX42_END
