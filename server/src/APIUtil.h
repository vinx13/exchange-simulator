#ifndef EXCHANGESIMULATOR_SERVER_APIUTIL_H
#define EXCHANGESIMULATOR_SERVER_APIUTIL_H


#include "Quote.h"
#include "TradeRecord.h"
#include "SecurityStatus.h"

#include <string>
#include <memory>
#include <cppconn/statement.h>

class APIUtil {
public:
    typedef std::shared_ptr<sql::Statement> StmtPtr;

    static void securityTryLock(StmtPtr stmt, const std::string &symbol, bool &result);

    static void securityUnlock(StmtPtr stmt, const std::string &symbol);

    static void securityUpdatePrice(StmtPtr stmt, const SecurityStatus &security);

    static void securityQuery(StmtPtr stmt, const std::string &symbol);

    static void orderbookPut(StmtPtr stmt, const Quote &quote);

    static void orderbookDelete(StmtPtr stmt, const int quote_id);

    static void orderbookQueryMatch(StmtPtr stmt, const std::string &symbol);

    static void orderbookUpdate(StmtPtr stmt, const int quote_id, const int quantity);

    static void systemStatusIsRunning(StmtPtr stmt, bool &result);

    static void tradeRecordPut(StmtPtr stmt, const TradeRecord &record);
};


#endif //EXCHANGESIMULATOR_SERVER_APIUTIL_H
