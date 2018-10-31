#include "log.hpp"

#include <cstdarg>
#include <cstdio>
#include <iostream>

namespace cayv {

std::string formatv(std::string fmt, va_list v)
{
    if (fmt.empty()) return "";

    std::string rstr;
    size_t pos = 0;
    size_t n = 0;

    while ((n = fmt.find('{', pos)) != std::string::npos) {
        rstr.append(fmt.substr(pos, n - pos));
        if (fmt.size() <= n + 1) {
            log(WARN, "formatv: Unexpected end of string after '{{'");
            return CAYV_BADFORMATV;
        }
        int d;
        double f;
        char* cs;
        std::string cpps;
        switch (fmt[n + 1]) {
        case '{':
            rstr.append("{");
            pos = n + 2;
            break;
        case 'S': // cstring
            cs = va_arg(v, char*);
            rstr.append(cs);
            pos = n + 3;
            break;
        case 'f': // float/double
            f = va_arg(v, double);
            rstr.append(std::to_string(f));
            pos = n + 3;
            break;
        case 'i': // integer
        case 'd':
            d = va_arg(v, int);
            rstr.append(std::to_string(d));
            pos = n + 3;
            break;
        }

        if (fmt.size() <= pos - 1) {
            log(WARN, "formatv: Unexpected end of string");
            return CAYV_BADFORMATV;
        }
    }

    rstr.append(fmt.substr(pos));

    return rstr;
}

void log(LogLevel l, std::string fmt, ...)
{
    if (l < CAYV_LOGLEVEL) return;

    va_list v;
    va_start(v, fmt);

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

    std::cout << formatv("[" + p + "] " + fmt, v) << "\n";

    va_end(v);
}

}
