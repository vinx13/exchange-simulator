#include "RepeatGroup.h"

__FIX42_BEGIN

std::string Fix42::RepeatGroup::toString() const {
    std::string result = std::to_string(container_.count()) + DELIMITER;
    for (auto field_pair: container_)
        result += std::to_string(field_pair.first) + '=' + field_pair.second->toString();
    return result;
}

__FIX42_END
