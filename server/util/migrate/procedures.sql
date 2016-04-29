
use ExchangeSimulator;

DELIMITER //


CREATE PROCEDURE orderbook_put
(IN symbol TEXT, IN client TEXT, IN client_order_id TEXT, IN side CHAR(1), IN price INT, IN quantity INT)
BEGIN
    INSERT INTO `OrderBook`(`symbol`, `client`, `client_order_id`, `side`, `price`, `quantity`)
    VALUES(symbol, client, client_order_id, side, price, quantity);
END//


CREATE PROCEDURE orderbook_query
(IN symbol TEXT, IN side CHAR(1), IN price INT)
BEGIN
    SELECT `id`, `symbol`, `client`, `client_order_id`, `price`, `quantity`
    FROM `OrderBook`
    WHERE `symbol` = symbol AND `side` = side AND `price` = price
    ORDER BY `time` DESC;
END//


CREATE PROCEDURE orderbook_query_match(IN symbol TEXT)
BEGIN
    SELECT * FROM `OrderBook` WHERE
        `symbol` = symbol AND
        `price` in (
            SELECT `price` FROM `OrderBook` GROUP BY `price` HAVING
                COUNT(DISTINCT(`side`)) > 1
        ) ORDER BY `price`, `time` DESC;
END//

CREATE PROCEDURE orderbook_update(IN id TEXT, IN quantity INT)
BEGIN
    UPDATE `OrderBook` SET `quantity` = quantity WHERE `id` = id;
END//


CREATE PROCEDURE security_lock
(IN symbol TEXT)
BEGIN
    UPDATE `security` SET `lock` = TRUE WHERE `symbol` = symbol;
END//


CREATE PROCEDURE security_unlock
(IN symbol TEXT)
BEGIN
    UPDATE `security` SET `lock` = FALSE WHERE `symbol` = symbol;
END//


CREATE PROCEDURE security_unlock_all()
BEGIN
    UPDATE `security` SET `lock` = FALSE;
END//


DELIMITER ;