#ifndef EXCHANGESIMULATOR_FIX42_EXCEPTIONS_H
#define EXCHANGESIMULATOR_FIX42_EXCEPTIONS_H


#include "Common.h"
#include <exception>

__FIX42_BEGIN

struct MessageParserError : public std::exception {
public:
    MessageParserError(const char *message = "Message parser error") : message_(message) { }

    const char *what() const noexcept { return message_; }

private:
    const char *message_;
};

struct BadFieldType : public MessageParserError {
    BadFieldType(const char *message = "Bad field type") : MessageParserError(message) { }
};

struct BadFieldValue : public MessageParserError {
    BadFieldValue(const char *message = "Bad field value") : MessageParserError(message) { }
};

struct BadTag : public MessageParserError {
    BadTag(const char *message = "Bad tag") : MessageParserError(message) { }
};

struct DuplicateTag : public MessageParserError {
    DuplicateTag(const char *message = "Duplicate tag in field group") : MessageParserError(message) { }
};

__FIX42_END

#endif //EXCHANGESIMULATOR_FIX42_EXCEPTIONS_H
