# Server design guide 
## Thread model
1. Master thread start to listen to a specific socket after server is started
2. After a new connection arrives, the new file descriptor is put into a queue of certain worker thread.
3. The worker thread is notified by master thread with socket to fetch file descriptor of the new connection and register it in event loop maintained by libevent
4. When the worker thread receives a new message, a callback is invoked by libevent. 'dispatcher' choose a handler based on message type to generate response.
5. The response is serialized to c string and added to write-buffer of libevent.

## Concurrency and data synchronization
All data is store in database and each security has a 'lock' field in database. New orders are inserted to orderbook in database after validation. Then, 'lock' field is set to '1' and server starts to execute matching orders. After that, new trade records are added to database and 'lock' field is set to '0'.

## Design of database
### Table 'Orderbook'
Fields:  
id, symbol, client, client_order_id, side, price, ori_quantity, quantity, time

### Table 'Security'  
Fields:  
symbol, price, prev_close, mkt_cap, trading_status, lock  

### Table 'TradeRecord'
Fields:  
id, order_buy, order_sell, price, quantity, time


