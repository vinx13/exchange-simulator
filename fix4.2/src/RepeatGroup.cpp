#include "RepeatGroup.h"

__FIX42_BEGIN

std::string Fix42::RepeatGroup::toString() const {
    std::string result = std::to_string(groups_.size()) + DELIMITER;
    for(auto group : groups_) {
        for (auto field_pair: *group)
            result += std::to_string(field_pair.first) + '=' + field_pair.second->toString();
    }
    return result;
}

__FIX42_END
