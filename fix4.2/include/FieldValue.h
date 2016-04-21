#ifndef EXCHANGESIMULATOR_FIX42_FIELDVALUE_H
#define EXCHANGESIMULATOR_FIX42_FIELDVALUE_H


#include "Common.h"
#include "Exceptions.h"
#include <string>
#include <vector>


__FIX42_BEGIN

class FieldValue {
public:

    static FieldValuePtr fromString(const kFieldType type, const std::string &s);

    static FieldValuePtr fromString(const kFieldType type,
                                    std::string::const_iterator begin,
                                    std::string::const_iterator end);

    virtual std::string toString() const = 0;

    ~FieldValue() { }
};

class IntFieldValue : public FieldValue {
public:

    explicit IntFieldValue(const int value) : value_(value) { }

    virtual std::string toString() const;

    int getValue() const { return value_; }

private:
    int value_;
};


class LengthFieldValue : public FieldValue {
public:
    explicit LengthFieldValue(size_t value) : value_(value) { }

    virtual std::string toString() const;

    size_t getValue() const { return value_; }

private:
    size_t value_;
};

class CharFieldValue : public FieldValue {
public:

    explicit CharFieldValue(const char value) : value_(value) { }

    virtual std::string toString() const;

    char getValue() const { return value_; }

private:
    char value_;
};

class StringFieldValue : public FieldValue {
public:

    StringFieldValue(std::string::const_iterator begin, std::string::const_iterator end) : value_(begin, end) { }

    explicit StringFieldValue(const std::string s) : value_(s) { }

    virtual std::string toString() const;

    const std::string &getValue() const { return value_; }

private:
    std::string value_;
};

class FloatFieldValue : public FieldValue {
public:

    explicit FloatFieldValue(double value) : value_(value) { }

    virtual std::string toString() const;

    double getValue() const { return value_; }

private:
    double value_;
};

class DataFieldValue : public FieldValue {
public:
    DataFieldValue(std::string::const_iterator begin, std::string::const_iterator end) {
        value_ = new char[end - begin];
        std::copy(begin, end, value_);
        len_ = end - begin;
    }

    DataFieldValue(const char *data, int len) : len_(len) {
        value_ = new char[len];
        std::copy(data, data + len, value_);
    }

    ~DataFieldValue() { delete[] value_; }

    virtual std::string toString() const;

    const char *getValue() const { return value_; }

    size_t getLength() const { return len_; }

private:
    char *value_;
    size_t len_;
};


template<kFieldType>
struct FieldValueType {
};

#define DECLARE_TYPE_MAP(ENUM_VALUE, TYPE) \
    template<> \
    struct FieldValueType<kFieldType::ENUM_VALUE>{ \
        typedef TYPE Type; \
    };

DECLARE_TYPE_MAP(kChar, CharFieldValue)
DECLARE_TYPE_MAP(kInt, IntFieldValue)
DECLARE_TYPE_MAP(kData, DataFieldValue)
DECLARE_TYPE_MAP(kString, StringFieldValue)
DECLARE_TYPE_MAP(kFloat, FloatFieldValue)
DECLARE_TYPE_MAP(kLength, LengthFieldValue)


__FIX42_END

#endif //EXCHANGESIMULATOR_FIX42_FIELDVALUE_H
