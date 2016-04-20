#ifndef EXCHANGESIMULATOR_FIX42_REPEATGROUP_H
#define EXCHANGESIMULATOR_FIX42_REPEATGROUP_H


#include "Common.h"
#include "FieldContainer.h"
#include <vector>
#include <memory>


__FIX42_BEGIN

class RepeatGroup {
public:
    int count() const { return container_.count(); }

    FieldValueContainer &getGroups() { return container_; }

    const FieldValueContainer &getValueContainer() const { return container_; }

    std::string toString() const;

private:
    FieldValueContainer container_;
};

__FIX42_END

#endif //EXCHANGESIMULATOR_FIX42_REPEATGROUP_H
