#ifndef EXCHANGESIMULATOR_FIX42_MESSAGEPARSER_H
#define EXCHANGESIMULATOR_FIX42_MESSAGEPARSER_H


#include "Common.h"
#include "FieldValue.h"
#include "Exceptions.h"
#include <string>

__FIX42_BEGIN

class MessageParser {
public:
    MessageParser(std::string::iterator begin, std::string::iterator end) : begin_(begin), end_(end) { }

    Tag goNextTag();

    FieldValuePtr goNextFieldValue(kFieldType type, size_t len = -1);

    void goLastStart();

    bool isDone() const;

private:
    const std::string::iterator begin_;
    std::string::iterator current_, end_;
};

__FIX42_END

#endif //EXCHANGESIMULATOR_FIX42_MESSAGEPARSER_H
