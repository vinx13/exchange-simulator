#ifndef EXCHANGESIMULATOR_FIX42_FIELDCONTAINER_H
#define EXCHANGESIMULATOR_FIX42_FIELDCONTAINER_H

#include "Common.h"
#include "Exceptions.h"
#include "FieldValue.h"
#include <map>
#include <memory>

__FIX42_BEGIN

template<class T>
class FieldContainer {
public:

    typedef std::shared_ptr<T> PtrType;
    typedef std::map<Tag, PtrType> Container;

    const PtrType get(Tag tag) const noexcept {
        auto it = fields_.find(tag);
        return (it != fields_.cend()) ?
               it->second : FieldValuePtr();
    }

    void set(Tag tag, PtrType value, bool override = true) throw(DuplicateTag) {
        if (override || fields_.find(tag) == fields_.end()) {
            //override or key does not exist
            fields_[tag] = value;
            return;
        }
        throw DuplicateTag();
    }

    bool contains(Tag tag) const noexcept {
        return fields_.find(tag) != fields_.cend();
    }

    std::string toString() const noexcept {
        std::string result;
        for (auto field: fields_) {
            result += std::to_string(field.first) + '=' + field.second->toString() + DELIMITER;
        }
        return result;
    }

    Container::size_type count() const {
        return fields_.size();
    };

    Container::iterator begin() { return fields_.begin(); }
    Container::iterator end() { return fields_.end(); }
    Container::const_iterator begin() const { return fields_.begin(); }
    Container::const_iterator end() const { return fields_.end(); }

private:
    Container fields_;
};

class FieldValue;
class RepeatGroup;

typedef FieldContainer<FieldValue> FieldValueContainer;
typedef FieldContainer<RepeatGroup> RepeatGroupContainer;

__FIX42_END

#endif //EXCHANGESIMULATOR_FIX42_FIELDGROUP_H
