CREATE PROCEDURE security_try_lock
(IN symbol TEXT, out result BOOLEAN)
BEGIN
    DECLARE locked BOOLEAN;
    SET result = FALSE;
    SELECT `lock` INTO locked FROM `Security` WHERE `symbol` = symbol LIMIT 1;
    IF locked is FALSE THEN
        SET AUTOCOMMIT = 0;
        START TRANSACTION;
            SELECT `lock` INTO locked FROM `Security` WHERE `symbol` = symbol LIMIT 1;
            IF locked is FALSE THEN
                UPDATE `Security` SET `lock` = TRUE WHERE `symbol` = symbol;
                SET result = TRUE;
            END IF;
        COMMIT;
        SET AUTOCOMMIT = 1;
    END IF;
END//


CREATE PROCEDURE security_unlock
(IN symbol TEXT)
BEGIN
    UPDATE `Security` SET `lock` = FALSE WHERE `symbol` = symbol;
END//


CREATE PROCEDURE security_unlock_all()
BEGIN
    UPDATE `Security` SET `lock` = FALSE;
END//

CREATE PROCEDURE security_update_price(IN symbol TEXT, IN price INT)
BEGIN
    UPDATE `Security` SET `price` = price WHERE `symbol` = symbol;
END//