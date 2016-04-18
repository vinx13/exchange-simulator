#ifndef EXCHANGESIMULATOR_FIX42_FIELDGROUP_H
#define EXCHANGESIMULATOR_FIX42_FIELDGROUP_H

#include "fix4.2/include/Common.h"
#include "fix4.2/include/Exceptions.h"
#include <map>
#include <memory>

__FIX42_BEGIN

class FieldValue;

class FieldGroup {
public:
    const FieldValuePtr get(Tag tag) const noexcept ;

    void set(Tag tag, FieldValuePtr value, bool override = true) throw(DuplicateTag);

    bool contains(Tag tag) const noexcept ;

private:
    std::map<Tag, FieldValuePtr> fields_;
};


__FIX42_END

#endif //EXCHANGESIMULATOR_FIX42_FIELDGROUP_H
