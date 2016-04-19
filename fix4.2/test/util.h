#ifndef EXCHANGESIMULATOR_FIX42_TEST_UTIL_H
#define EXCHANGESIMULATOR_FIX42_TEST_UTIL_H

#include "fix4.2/Fix42.h"

/* create smart pointer to FieldValue from string */
template<Fix42::kFieldType FIELD_TYPE>
static std::shared_ptr<
        typename Fix42::FieldValueType<FIELD_TYPE>::Type>
fromString(const char *s) {
    return std::static_pointer_cast<
            typename Fix42::FieldValueType<FIELD_TYPE>::Type>(
            Fix42::FieldValue::fromString(FIELD_TYPE, std::string(s))
    );
}

/* create smarter pointer to FieldValue from its constructor directly */
template<Fix42::kFieldType FIELD_TYPE, class ...Arg>
static std::shared_ptr<
        typename Fix42::FieldValueType<FIELD_TYPE>::Type>
fromValue(Arg ...arg) {
    return std::make_shared<typename Fix42::FieldValueType<FIELD_TYPE>::Type>(std::forward<Arg>(arg)...);
};

#endif //EXCHANGESIMULATOR_FIX42_TESTUTIL_H
