#ifndef EXCHANGESIMULATOR_FIX42_REPEATGROUP_H
#define EXCHANGESIMULATOR_FIX42_REPEATGROUP_H


#include "Common.h"
#include "FieldContainer.h"
#include <vector>
#include <memory>


__FIX42_BEGIN

/* A repeating group is comprised with multiple field containers (repeating unit) */
class RepeatGroup {
public:
    int count() const { return groups_.size(); }

    std::vector<FieldValueContainerPtr> &getGroups() { return groups_; }

    const std::vector<FieldValueContainerPtr> &getGroups() const { return groups_; }

    std::string toString() const;

private:
    std::vector<FieldValueContainerPtr> groups_;
};

__FIX42_END

#endif //EXCHANGESIMULATOR_FIX42_REPEATGROUP_H
