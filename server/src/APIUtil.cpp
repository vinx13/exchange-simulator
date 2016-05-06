#include "APIUtil.h"
#include "TradeRecord.h"
#include <sstream>

void APIUtil::securityTryLock(APIUtil::StmtPtr stmt, const std::string &symbol, bool &result) {
    std::ostringstream s;
    s << "CALL security_try_lock('" << symbol << "', @result)";
    stmt->execute(s.str());
    std::shared_ptr<sql::ResultSet> results(stmt->executeQuery("SELECT @result AS _result"));
    results->next();
    result = results->getBoolean("_result");
}

void APIUtil::securityUnlock(APIUtil::StmtPtr stmt, const std::string &symbol) {
    std::ostringstream s;
    s << "CALL security_unlock('" << symbol << "')";
    stmt->execute(s.str());
}

void APIUtil::orderbookPut(APIUtil::StmtPtr stmt, const Quote &quote) {
    std::ostringstream s;
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
    std::ostringstream s;
    s << "CALL orderbook_delete(" << quote_id << ")";
    stmt->execute(s.str());
}

void APIUtil::orderbookQueryMatch(StmtPtr stmt, const std::string &symbol) {
    std::ostringstream s;
    s << "CALL orderbook_query_match('" << symbol << "')";
    stmt->execute(s.str());
}

void APIUtil::orderbookUpdate(StmtPtr stmt, const int quote_id, const int quantity) {
    std::ostringstream s;
    s << "CALL orderbook_update(" << quote_id << "," << quantity << ")";
    stmt->execute(s.str());
}

void APIUtil::systemStatusIsRunning(StmtPtr stmt, bool &result) {
    stmt->execute("CALL systemstatus_is_running(@result)");
    std::shared_ptr<sql::ResultSet> results(stmt->executeQuery("SELECT @result AS _result"));
    results->next(); //only one result exists
    result = results->getBoolean("_result");
}

void APIUtil::tradeRecordPut(StmtPtr stmt, const TradeRecord &record) {
    std::ostringstream s;
    s << "CALL traderecord_put("
    << record.order_buy << ","
    << record.order_sell << ","
    << record.price << ","
    << record.quantity << ")";
    stmt->execute(s.str());
}

void APIUtil::securityUpdatePrice(StmtPtr stmt, const SecurityStatus &security){
    std::ostringstream s;
    s << "CALL security_update_price('"
    << security.symbol << "',"
    << security.price << ")";
    stmt->execute(s.str());
}

void APIUtil::securityQuery(StmtPtr stmt, const std::string &symbol) {
    std::ostringstream s;
    s << "CALL security_query('" << symbol << "')";
    stmt->execute(s.str());
}
