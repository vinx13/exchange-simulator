#ifndef EXCHANGESIMULATOR_FIX42_FIELDTYPEMAP_H
#define EXCHANGESIMULATOR_FIX42_FIELDTYPEMAP_H


#include "Common.h"
#include <memory>
#include <map>

__FIX42_BEGIN

class FieldTypeMap {
public:
    kFieldType get(Tag tag) { return map_[tag]; }

    kFieldType get(kFieldName name) { return map_[Tag(name)]; };

    static const FieldTypeMapPtr getInstance() { return instance_; }

private:
    FieldTypeMap();

    static FieldTypeMapPtr instance_;
    std::map<Tag, kFieldType> map_;

};

__FIX42_END

#endif //EXCHANGESIMULATOR_FIX42_FIELDTYPEMAP_H
