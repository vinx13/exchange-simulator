#ifndef EXCHANGESIMULATOR_SERVER_ORDERHANDLER_H
#define EXCHANGESIMULATOR_SERVER_ORDERHANDLER_H


#include "Fix42.h"
#include "MessageHandler.h"
#include "Quote.h"
#include "APIUtil.h"

#include <vector>
#include <memory>

class OrderHandler : public MessageHandler {
public:

    OrderHandler(APIUtil::ConnPtr conn) : dbconn_(conn) { }

    virtual std::vector<Fix42::MessagePtr> accept(const Fix42::MessagePtr message) override;

    void handleSingleOrder(const Quote &quote, std::vector<Fix42::MessagePtr> &results);

private:
    APIUtil::ConnPtr dbconn_;

    Fix42::MessagePtr createMsgAccept(const Quote &quote);

    Fix42::MessagePtr createMsgReject(const Quote &quote);

    void addBasicFields(const Quote &quote, std::shared_ptr<Fix42::Message> &message) const;


};


#endif //EXCHANGESIMULATOR_SERVER_ORDERHANDLER_H
