#ifndef EXCHANGESIMULATOR_FIX42_COMMON_H
#define EXCHANGESIMULATOR_FIX42_COMMON_H

#ifndef __FIX42_BEGIN
#define __FIX42_BEGIN namespace Fix42{
#endif

#ifndef __FIX42_END
#define __FIX42_END }
#endif

#include <string>
#include <memory>

__FIX42_BEGIN
class FieldValue;
typedef std::string::iterator StrIterator;
typedef std::shared_ptr<FieldValue> FieldValuePtr;
typedef int Tag;

enum kFieldType {
    Int, Char, Float, String, Data
};
const char DELIMITER = '\001';

__FIX42_END


#endif //EXCHANGESIMULATOR_FIX42_COMMON_H
