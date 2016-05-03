#include "APIUtil.h"
#include <sstream>

void APIUtil::securityLock(APIUtil::StmtPtr stmt, const std::string &symbol) {
    std::istringstream s;
    s << "CALL security_lock('" + symbol + "')";
    stmt->execute(s.str());
}

void APIUtil::securityUnlock(APIUtil::StmtPtr stmt, const std::string &symbol) {
    std::istringstream s;
    s << "CALL security_unlock('" + symbol + "')";
    stmt->execute(query);
}

void APIUtil::orderbookPut(APIUtil::StmtPtr stmt, const Quote &quote) {
    std::istringstream s;
    s << "CALL orderbook_put("
    << "'" << quote.symbol.c_str() << "',"
    << "'" << quote.client.c_str() << "',"
    << "'" << quote.client_order_id.c_str() << "',"
    << "'" << static_cast<char>(quote.side) << "',"
    << quote.price << ","
    << quote.quantity << ")";
    stmt->execute(s.str());
}

void APIUtil::orderbookDelete(APIUtil::StmtPtr stmt, const int quote_id) {
    std::istringstream s;
    s << "CALL orderbook_delete(" << quote_id << ")";
    stmt->execute(s.str());
}

void APIUtil::orderbookQueryMatch(StmtPtr stmt, const std::string &symbol) {
    std::istringstream s;
    s << "CALL orderbook_query_match('" << symbol << ")";
    stmt->execute(s.str());
}

void APIUtil::orderbookUpdate(StmtPtr stmt, const int quote_id, const int quantity) {
    std::istringstream s;
    s << "CALL orderbook_update(" << quote_id << "," << quantity << ")";
    stmt->execute(s.str());
}