CREATE PROCEDURE traderecord_put(IN order_buy INT, IN order_sell INT, IN price INT, IN quantity INT)
BEGIN
    INSERT INTO `TradeRecord`(`order_buy`, `order_sell`, `price`, `quantity`)
    VALUES (order_buy, order_sell, price, quantity);
END