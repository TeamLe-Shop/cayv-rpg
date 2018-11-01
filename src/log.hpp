#pragma once

#include <string>
#include "format.h"

#define CAYV_LOGLEVEL DEBUG

namespace cayv {

enum LogLevel {
    DEBUG = 0, INFO = 1, WARN = 2, SEVERE = 3
};

template <typename... Args>
void log(LogLevel l, std::string fmt, Args&&... args)
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

    std::string msg = fmt::format(fmt, std::forward<Args>(args)...);

    fmt::print(stderr, "[{}] {}\n", p, msg);
}

}
