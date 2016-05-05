CREATE PROCEDURE systemstatus_is_running(OUT result BOOLEAN)
BEGIN
    SELECT `running` INTO result FROM `SystemStatus` LIMIT 1;
END