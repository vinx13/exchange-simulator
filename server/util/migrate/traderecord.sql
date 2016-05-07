CREATE PROCEDURE traderecord_put(IN order_buy_ INT, IN order_sell_ INT, IN price_ INT, IN quantity_ INT)
BEGIN
    INSERT INTO `TradeRecord`(`order_buy`, `order_sell`, `price`, `quantity`)
    VALUES (order_buy_, order_sell_, price_, quantity_);
END