#ifndef EXCHANGESIMULATOR_SERVER_MESSAGEHANDLER_H
#define EXCHANGESIMULATOR_SERVER_MESSAGEHANDLER_H


#include "APIUtil.h"

class MessageHandler {
public:

    MessageHandler(APIUtil::ConnPtr conn) : api_(conn) { }

    virtual std::vector<Fix42::MessagePtr> accept(const Fix42::MessagePtr message) = 0;

    ~MessageHandler() { }

protected:
    APIUtil api_;
};


#endif //EXCHANGESIMULATOR_SERVER_MESSAGEHANDLER_H
