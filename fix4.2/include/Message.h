#ifndef EXCHANGESIMULATOR_FIX42_MESSAGE_H
#define EXCHANGESIMULATOR_FIX42_MESSAGE_H


#include "Common.h"
#include "MessageParser.h"
#include "RepeatGroup.h"
#include "FieldContainer.h"
#include <string>
#include <vector>

__FIX42_BEGIN

class Message {
public:
    explicit Message(std::string s);

    Message(std::string::iterator begin, std::string::iterator end);

    const FieldValuePtr getField(Tag tag) const;
    const FieldValuePtr getField(kFieldName name) const;
    const RepeatGroupPtr getRepeatGroup(Tag tag) const;
    const RepeatGroupPtr getRepeatGroup(kFieldName name) const;
    FieldValuePtr getField(Tag tag);
    FieldValuePtr getField(kFieldName name);
    RepeatGroupPtr getRepeatGroup(Tag tag);
    RepeatGroupPtr getRepeatGroup(kFieldName name);

protected:
    MessageParser parser_;

    void parse();

    FieldValueContainer field_values_;
    RepeatGroupContainer repeat_groups_;

};

__FIX42_END

#endif //EXCHANGESIMULATOR_FIX42_MESSAGE_H
