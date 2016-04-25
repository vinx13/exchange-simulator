#ifndef EXCHANGESIMULATOR_FIX42_MESSAGE_H
#define EXCHANGESIMULATOR_FIX42_MESSAGE_H


#include "Common.h"
#include "MessageParser.h"
#include "RepeatGroup.h"
#include "FieldContainer.h"
#include "FieldTypeMap.h"
#include <string>
#include <vector>

__FIX42_BEGIN

class Message {
public:

    //template alias
    template<kFieldName name>
    using __FieldValueType = typename FieldValueType<FieldTypeMap::get(name)>::Type;
    template<kFieldName name>
    using __FieldValuePtrType = std::shared_ptr<__FieldValueType<name>>;
    template<kFieldName name>
    using __FieldValueConstPtrType = typename std::add_const<__FieldValuePtrType<name> >::type;


    explicit Message(std::string s);

    Message(std::string::iterator begin, std::string::iterator end);

    RepeatGroupPtr getRepeatGroup(kFieldName name) { return repeat_groups_.get(static_cast<Tag>(name)); }

    const RepeatGroupPtr getRepeatGroup(kFieldName name) const { return repeat_groups_.get(static_cast<Tag>(name)); }

    /*
    template<kFieldName name>
    __FieldValuePtrType<name> getField() {
        return std::static_pointer_cast<__FieldValueType<name>>(
                field_values_.get(static_cast<Tag>(name))
        );
    }
    */

    template<kFieldName name>
    __FieldValueConstPtrType<name> getField() const {
        return std::static_pointer_cast<__FieldValueType<name>>(
                field_values_.get(static_cast<Tag>(name))
        );
    }

protected:
    MessageParser parser_;

    void parse();

    FieldValueContainer field_values_;
    RepeatGroupContainer repeat_groups_;

};

__FIX42_END

#endif //EXCHANGESIMULATOR_FIX42_MESSAGE_H
