#ifndef EXCHANGESIMULATOR_FIX42_MESSAGEPARSER_H
#define EXCHANGESIMULATOR_FIX42_MESSAGEPARSER_H


#include "Common.h"
#include "FieldValue.h"
#include "Exceptions.h"
#include <string>

__FIX42_BEGIN

class MessageParser {
public:
    MessageParser(std::string::const_iterator begin, std::string::const_iterator end) :
            begin_(begin), end_(end), current_(begin) { }

    Tag goNextTag();

    FieldValuePtr goNextFieldValue(kFieldType type, size_t len = -1);

    void goLastStart();

    bool isDone() const;

private:
    const std::string::const_iterator begin_, end_;
    std::string::const_iterator current_;
};

__FIX42_END

#endif //EXCHANGESIMULATOR_FIX42_MESSAGEPARSER_H
