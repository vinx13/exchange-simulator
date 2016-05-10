CREATE PROCEDURE security_try_lock
(IN symbol_ TEXT, out result BOOLEAN)
BEGIN
    DECLARE locked BOOLEAN;
    SET result = FALSE;
    SELECT `lock` INTO locked FROM `Security` WHERE `symbol` = symbol_ LIMIT 1;
    IF locked is FALSE THEN
        SET AUTOCOMMIT = 0;
        START TRANSACTION;
            SELECT `lock` INTO locked FROM `Security` WHERE `symbol` = symbol_ LIMIT 1;
            IF locked is FALSE THEN
                UPDATE `Security` SET `lock` = TRUE WHERE `symbol` = symbol_;
                SET result = TRUE;
            END IF;
        COMMIT;
        SET AUTOCOMMIT = 1;
    END IF;
END//


CREATE PROCEDURE security_unlock
(IN symbol_ TEXT)
BEGIN
    UPDATE `Security` SET `lock` = FALSE WHERE `symbol` = symbol_;
END//


CREATE PROCEDURE security_unlock_all()
BEGIN
    UPDATE `Security` SET `lock` = FALSE;
END//

CREATE PROCEDURE security_update_price(IN symbol_ TEXT, IN price_ INT)
BEGIN
    UPDATE `Security` SET `price` = price_ WHERE `symbol` = symbol_;
END//

CREATE PROCEDURE security_query(IN symbol_ TEXT)
BEGIN
    SELECT * from `Security` WHERE `symbol` = symbol_;
END//

CREATE PROCEDURE security_stop_trading(IN symbol_ TEXT)
BEGIN
    UPDATE `Security` SET `trading` = FALSE WHERE `symbol` = symbol_;
END//

CREATE PROCEDURE security_start_trading(IN symbol_ TEXT)
BEGIN
    UPDATE `Security` SET `trading` = TRUE WHERE `symbol` = symbol_;
END//