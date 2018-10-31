#pragma once

#include <string>

#define CAYV_LOGLEVEL DEBUG
#define CAYV_BADFORMATV "formatv: error"

namespace cayv {

enum LogLevel {
    DEBUG = 0, INFO = 1, WARN = 2, SEVERE = 3
};

std::string formatv(std::string fmt, va_list v);

void log(LogLevel l, std::string fmt, ...);

}
