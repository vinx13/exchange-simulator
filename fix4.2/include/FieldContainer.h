#ifndef EXCHANGESIMULATOR_FIX42_FIELDCONTAINER_H
#define EXCHANGESIMULATOR_FIX42_FIELDCONTAINER_H

#include "Common.h"
#include "Exceptions.h"
#include "FieldValue.h"
#include <map>
#include <memory>

__FIX42_BEGIN

/* Top level field container, storing fields and repeating groups */
template<class T>
class FieldContainer {
public:

    typedef std::shared_ptr<T> PtrType;
    typedef std::map<Tag, PtrType> Container;

    const PtrType get(Tag tag) const noexcept {
        auto it = fields_.find(tag);
        return (it != fields_.end()) ?
               it->second : PtrType();
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
            result += std::to_string(field.first) + '=' + field.second->toString();
        }
        return result;
    }

    typename Container::size_type count() const {
        return fields_.size();
    };

    typename Container::iterator begin() { return fields_.begin(); }
    typename Container::iterator end() { return fields_.end(); }
    typename Container::const_iterator begin() const { return fields_.begin(); }
    typename Container::const_iterator end() const { return fields_.end(); }

private:
    Container fields_;
};

class FieldValue;
class RepeatGroup;

typedef FieldContainer<FieldValue> FieldValueContainer;
typedef FieldContainer<RepeatGroup> RepeatGroupContainer;
typedef std::shared_ptr<FieldValueContainer> FieldValueContainerPtr;
typedef std::shared_ptr<RepeatGroupContainer> RepeatGroupContainerPtr;

__FIX42_END

#endif //EXCHANGESIMULATOR_FIX42_FIELDCONTAINER_H
