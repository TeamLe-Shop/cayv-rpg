#pragma once

#include <string>
#include "format.h"

#define CAYV_LOGLEVEL DEBUG
#define CAYV_BADFORMATV "formatv: error"

namespace cayv {

enum LogLevel {
    DEBUG = 0, INFO = 1, WARN = 2, SEVERE = 3
};

template <typename... Args>
void log(LogLevel l, std::string fmt, const Args&... args)
{
    if (l < CAYV_LOGLEVEL) return;

    std::string p;

    switch (l) {
    case DEBUG:
        p = "DEBUG";
        break;
    case INFO:
        p = "INFO";
        break;
    case WARN:
        p = "WARN";
        break;
    case SEVERE:
        p = "SEVERE";
        break;
    }

    std::string msg = fmt::format(fmt, args...);

    fmt::print(stderr, "[{}] {}", p, msg);
}

}
