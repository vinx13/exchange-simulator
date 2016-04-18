#ifndef EXCHANGESIMULATOR_FIX42_REPEATGROUP_H
#define EXCHANGESIMULATOR_FIX42_REPEATGROUP_H


#include "Common.h"
#include "FieldGroup.h"
#include <vector>
#include <memory>


__FIX42_BEGIN

class RepeatGroup {
public:
    typedef std::vector<FieldGroupPtr> Container;

    int count() const { return fields_.size(); }

    Container &getFields() { return fields_; }

    const Container &getFields() const { return fields_; }

    std::string toString() const;

private:
    Container fields_;
};

__FIX42_END

#endif //EXCHANGESIMULATOR_FIX42_REPEATGROUP_H
