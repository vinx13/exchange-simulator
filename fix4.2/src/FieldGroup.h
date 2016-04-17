#ifndef EXCHANGESIMULATOR_FIX42_FIELDGROUP_H
#define EXCHANGESIMULATOR_FIX42_FIELDGROUP_H


#include <map>
#include <memory>

class FieldValue;

class FieldGroup {
public:
    typedef int Tag;
    const std::shared_ptr<FieldValue *> get(Tag tag)const;
    bool set(Tag tag, std::shared_ptr<FieldValue *> value, bool override = true);
private:
    std::map<Tag, std::shared_ptr<FieldValue *> > fields_;
};

#endif //EXCHANGESIMULATOR_FIX42_FIELDGROUP_H
