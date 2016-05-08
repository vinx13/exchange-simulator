#ifndef EXCHANGESIMULATOR_LOGGER_H
#define EXCHANGESIMULATOR_LOGGER_H


#include "Config.h"

#include <string>
#include <mutex>
#include <memory>

class Logger {
public:
    enum class kLoggerLevel {
        kInfo, kDebug, kError
    };

    static std::shared_ptr<Logger> getLogger() { return instance__; }

    void info(const std::string &tag, const std::string &s);

    void debug(const std::string &tag, const std::string &s);

    void error(const std::string &tag, const std::string &s);

private:
    static std::shared_ptr<Logger> instance__;

    void print(const std::string &tag, const std::string &s, const kLoggerLevel level);

    std::string getFormatedTime() const;

    void addLogHead(std::ostream &dest, const std::string &tag, const kLoggerLevel level) const;

    std::string levelToString(const kLoggerLevel level) const;

    std::mutex mutex_;
};


#endif //EXCHANGESIMULATOR_LOGGER_H
