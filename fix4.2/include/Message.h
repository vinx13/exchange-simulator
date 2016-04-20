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

protected:
    MessageParser parser_;

    void parse();

    FieldValueContainer field_values_;
    RepeatGroupContainer repeat_groups_;

};

__FIX42_END

#endif //EXCHANGESIMULATOR_FIX42_MESSAGE_H
