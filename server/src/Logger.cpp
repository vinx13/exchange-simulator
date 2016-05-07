#include "Logger.h"

#include <ctime>
#include <sstream>
#include <iostream>

std::shared_ptr<Logger> Logger::instance__ = std::shared_ptr<Logger>(new Logger());

void Logger::info(const std::string &s) {
    print(s, kLoggerLevel::kInfo);
}

void Logger::debug(const std::string &s) {
    print(s, kLoggerLevel::kDebug);
}

void Logger::error(const std::string &s) {
    print(s, kLoggerLevel::kError);
}

void Logger::print(const std::string &s, const kLoggerLevel level) {
    std::ostringstream os;
    addLogHead(os, level);
    os << s << std::endl;
    std::string complete = os.str();
    std::lock_guard<std::mutex> lock(mutex_);
    if (Config::getGlobalConfig()->debug) {
        std::cout << complete;
    }
    //TODO write to log file
}


void Logger::addLogHead(std::ostream &dest, const Logger::kLoggerLevel level) const {
    dest << getFormatedTime() << ' ' << levelToString(level) << ' ';
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


