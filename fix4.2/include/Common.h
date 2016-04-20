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
class FieldGroup;
class RepeatGroup;
class FieldTypeMap;

typedef std::shared_ptr<FieldValue> FieldValuePtr;
typedef std::shared_ptr<FieldGroup> FieldGroupPtr;
typedef std::shared_ptr<RepeatGroup> RepeatGroupPtr;
typedef std::shared_ptr<FieldTypeMap> FieldTypeMapPtr;
typedef int Tag;

enum kFieldType {
    kInt, kChar, kFloat, kString, kData, kRepeatGroup
};

enum kFieldName {

};

const char DELIMITER = '\001';

__FIX42_END


#endif //EXCHANGESIMULATOR_FIX42_COMMON_H
