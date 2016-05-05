CREATE PROCEDURE security_lock
(IN symbol TEXT)
BEGIN
    UPDATE `Security` SET `lock` = TRUE WHERE `symbol` = symbol;
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
