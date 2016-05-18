# Exchange Simulator

##Dependency
- [libevent 2.0.22](http://libevent.org)
- [mysql-connector-c++ 1.1.6](http://dev.mysql.com/downloads/connector/cpp/)

##Build
```
mkdir build && cd build
cmake ../
make
```

##Database
MySQL 5.7  
To initiate local database, run:
```
./server/util/migrate/migrate.sh DB_USER DB_PASSWORD
```

##Platform
Currently only *nix is supported.
