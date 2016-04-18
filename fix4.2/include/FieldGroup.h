#ifndef EXCHANGESIMULATOR_FIX42_FIELDGROUP_H
#define EXCHANGESIMULATOR_FIX42_FIELDGROUP_H

#include "Common.h"
#include "Exceptions.h"
#include "FieldValue.h"
#include <map>
#include <memory>

__FIX42_BEGIN

class FieldValue;

class FieldGroup {
public:
    const FieldValuePtr get(Tag tag) const noexcept;

    void set(Tag tag, FieldValuePtr value, bool override = true) throw(DuplicateTag);

    bool contains(Tag tag) const noexcept;

    std::string toString() const noexcept;

private:
    std::map<Tag, FieldValuePtr> fields_;
};


__FIX42_END

#endif //EXCHANGESIMULATOR_FIX42_FIELDGROUP_H
