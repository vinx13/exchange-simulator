#ifndef EXCHANGESIMULATOR_LOGGER_H
#define EXCHANGESIMULATOR_LOGGER_H


#include "Config.h"

#include <string>
#include <mutex>
#include <memory>
#include <fstream>

class Logger {
public:
    enum class kLoggerLevel : int {
        kInfo = 0, kDebug = 1, kError = 2
    };

    static std::shared_ptr<Logger> getLogger();

    void info(const std::string &tag, const std::string &s);

    void debug(const std::string &tag, const std::string &s);

    void error(const std::string &tag, const std::string &s);

private:
    // use lazy instantiation as Logger must be instantiate after the global config is set
    static std::shared_ptr<Logger> instance__;

    Logger(std::string filename);

    void print(const std::string &tag, const std::string &s, const kLoggerLevel level);

    std::string getFormatedTime() const;

    void addLogHead(std::ostream &dest, const std::string &tag, const kLoggerLevel level) const;

    int levelCompareTo(const kLoggerLevel level) const;

    std::string levelToString(const kLoggerLevel level) const;

    std::mutex mutex_;

    kLoggerLevel level_ = kLoggerLevel::kInfo;


    std::ofstream log_stream_;
};


#endif //EXCHANGESIMULATOR_LOGGER_H
