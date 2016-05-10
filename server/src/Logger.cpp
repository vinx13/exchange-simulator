#include "Logger.h"

#include <ctime>
#include <sstream>
#include <iostream>

std::shared_ptr<Logger> Logger::instance__;

std::shared_ptr<Logger> Logger::getLogger() {
    if (instance__)
        return instance__;
    instance__.reset(new Logger(Config::getGlobalConfig()->logfile));
    return instance__;
}

Logger::Logger(std::string filename) : log_stream_(filename, std::fstream::app) { }

void Logger::info(const std::string &tag, const std::string &s) {
    print(tag, s, kLoggerLevel::kInfo);
}

void Logger::debug(const std::string &tag, const std::string &s) {
    print(tag, s, kLoggerLevel::kDebug);
}

void Logger::error(const std::string &tag, const std::string &s) {
    print(tag, s, kLoggerLevel::kError);
}

void Logger::print(const std::string &tag, const std::string &s, const kLoggerLevel level) {
    std::ostringstream os;
    addLogHead(os, tag, level);
    os << s << std::endl;
    std::string complete = os.str();
    std::lock_guard<std::mutex> lock(mutex_);
    if (Config::getGlobalConfig()->debug) {
        std::cout << complete;
    }
    if (log_stream_.is_open() && levelCompareTo(level) <= 0) {
        log_stream_ << complete;
    }
}


void Logger::addLogHead(std::ostream &dest, const std::string &tag, const Logger::kLoggerLevel level) const {
    dest << getFormatedTime() << " [" << levelToString(level) << "] " << tag << ": ";
}

std::string Logger::levelToString(const Logger::kLoggerLevel level) const {
    switch (level) {
        case kLoggerLevel::kInfo:
            return "INFO";
        case kLoggerLevel::kDebug:
            return "DEBUG";
        case kLoggerLevel::kError:
            return "ERROR";
    }
}


std::string Logger::getFormatedTime() const {
    char buf[40];
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buf, 40, "%F %T", timeinfo);
    return buf;
}

int Logger::levelCompareTo(const kLoggerLevel level) const {
    return static_cast<int>(level_) - static_cast<int>(level);
}
