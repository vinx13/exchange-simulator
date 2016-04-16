DROP DATABASE IF EXISTS ExchangeSimulator;
CREATE DATABASE ExchangeSimulator;

CREATE TABLE `ExchangeSimulator`.`OrderBook` (
    `symbol` TEXT NOT NULL ,
    `sender` TEXT NOT NULL ,
    `side` INT NOT NULL ,
    `price` INT NOT NULL ,
    `quantity` INT NOT NULL ,
    `time` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ,
    PRIMARY KEY (`symbol`(8))
    ) ENGINE = InnoDB;

CREATE TABLE `ExchangeSimulator`.`SecurityStatus` (
    `symbol` TEXT NOT NULL ,
    `price` INT NOT NULL ,
    `prev_close` INT NOT NULL ,
    `mkt_cap` BIGINT NOT NULL ,
    PRIMARY KEY (`symbol`(8))
    ) ENGINE = InnoDB;


