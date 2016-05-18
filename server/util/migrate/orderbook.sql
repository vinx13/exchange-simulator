CREATE PROCEDURE orderbook_put
(IN symbol_ TEXT, IN client_ TEXT, IN client_order_id_ TEXT, IN side_ CHAR(1), IN price_ INT, IN quantity_ INT)
BEGIN
    INSERT INTO `OrderBook`(`symbol`, `client`, `client_order_id`, `side`, `price`, `quantity`, `ori_quantity`)
    VALUES(symbol_, client_, client_order_id_, side_, price_, quantity_, quantity_);
    INSERT INTO `OrderArchive`(`symbol`, `client`, `client_order_id`, `side`, `price`, `quantity`, `ori_quantity`)
    VALUES(symbol_, client_, client_order_id_, side_, price_, quantity_, quantity_);
END//


CREATE PROCEDURE orderbook_query
(IN symbol_ TEXT, IN side_ CHAR(1), IN price_ INT)
BEGIN
    SELECT `id`, `symbol`, `client`, `client_order_id`, `price`, `quantity`
    FROM `OrderBook`
    WHERE `symbol` = symbol_ AND `side` = side_ AND `price` = price_
    ORDER BY `time` DESC;
END//

CREATE PROCEDURE orderbook_client_query
(IN client_ TEXT, IN client_order_id_ TEXT)
BEGIN
    SELECT `id`, `symbol`, `client`, `client_order_id`, `price`, `quantity`
    FROM `OrderBook`
    WHERE `client` = client_ AND `client_order_id` = client_order_id_
    LIMIT 1;
END//

CREATE PROCEDURE orderarchive_client_query
(IN client_ TEXT, IN client_order_id_ TEXT)
BEGIN
    SELECT `id`, `symbol`, `client`, `client_order_id`, `price`, `quantity`
    FROM `OrderArchive`
    WHERE `client` = client_ AND `client_order_id` = client_order_id_
    LIMIT 1;
END//

CREATE PROCEDURE orderbook_query_highest(IN symbol_ TEXT, IN side_ CHAR(1))
BEGIN
    SELECT `id`, `symbol`, `client`, `client_order_id`, `price`, `quantity`
    FROM `OrderBook`
    WHERE `symbol` = symbol_ AND `side` = side_
    ORDER BY `price` DESC, `time` DESC
    LIMIT 1;
END//

CREATE PROCEDURE orderbook_query_lowest(IN symbol_ TEXT, IN side_ CHAR(1))
BEGIN
    SELECT `id`, `symbol`, `client`, `client_order_id`, `price`, `quantity`
    FROM `OrderBook`
    WHERE `symbol` = symbol_ AND `side` = side_
    ORDER BY `price`, `time` DESC
    LIMIT 1;
END//

CREATE PROCEDURE orderbook_query_match(IN symbol_ TEXT)
BEGIN
    SELECT * FROM `OrderBook` WHERE
        `symbol` = symbol_ AND
        `price` in (
            SELECT `price` FROM `OrderBook` GROUP BY `price` HAVING
                COUNT(DISTINCT(`side`)) > 1
        ) ORDER BY `price`, `time` DESC;
END//

CREATE PROCEDURE orderbook_update(IN id_ TEXT, IN quantity_ INT)
BEGIN
    UPDATE `OrderBook` SET `quantity` = quantity_ WHERE `id` = id_;
END//

CREATE PROCEDURE orderbook_delete(IN id_ INT)
BEGIN
    DELETE FROM `OrderBook` WHERE `id` = id_;
END