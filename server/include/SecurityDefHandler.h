#ifndef EXCHANGESIMULATOR_SERVER_SECURITYDEFHANDLER_H
#define EXCHANGESIMULATOR_SERVER_SECURITYDEFHANDLER_H


#include "MessageHandler.h"
#include "APIUtil.h"

class SecurityDefHandler: public MessageHandler {
public:
    SecurityDefHandler(APIUtil::ConnPtr conn) : MessageHandler(conn) { }

    virtual std::vector<Fix42::MessagePtr> accept(const Fix42::MessagePtr message) override;

};


#endif //EXCHANGESIMULATOR_SERVER_SECURITYDEFHANDLER_H
