#include "RepeatGroup.h"

__FIX42_BEGIN

std::string Fix42::RepeatGroup::toString() const {
    std::string result = std::to_string(units_.size()) + DELIMITER;
    for(auto group : units_) {
        for (auto field_pair: *group)
            result += std::to_string(field_pair.first) + '=' + field_pair.second->toString();
    }
    return result;
}

__FIX42_END
