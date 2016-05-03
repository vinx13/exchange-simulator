#ifndef EXCHANGESIMULATOR_SERVER_APIUTIL_H
#define EXCHANGESIMULATOR_SERVER_APIUTIL_H


#include <string>
#include <memory>
#include <mysql_connection.h>

class APIUtil {
public:
    typedef std::shared_ptr<sql::Statement> StmtPtr;
    static void securityLock(StmtPtr stmt, const std::string &symbol);
    static void securityUnlock(StmtPtr stmt, const std::string &symbol);
    static void orderbookPut(StmtPtr stmt, const Quote &quote);
    static void orderbookDelete(StmtPtr stmt, const int quote_id);
    static void orderbookQueryMatch(StmtPtr stmt, const std::string &symbol);
    static void orderbookUpdate(StmtPtr stmt, const int quote_id, const int quantity);
};


#endif //EXCHANGESIMULATOR_SERVER_APIUTIL_H
