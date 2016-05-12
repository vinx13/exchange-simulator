#ifndef EXCHANGESIMULATOR_SERVER_SECURITYSTATUSHANDLER_H
#define EXCHANGESIMULATOR_SERVER_SECURITYSTATUSHANDLER_H


#include "Fix42.h"
#include "APIUtil.h"
#include "MessageHandler.h"

#include <vector>

class SecurityStatusHandler : public MessageHandler {
public:
    SecurityStatusHandler(APIUtil::ConnPtr conn) : MessageHandler(conn) { }

    virtual std::vector<Fix42::MessagePtr> accept(const Fix42::MessagePtr message) override;

};


#endif //EXCHANGESIMULATOR_SERVER_SECURITYSTATUSHANDLER_H
