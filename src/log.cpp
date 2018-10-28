#include "log.hpp"

#include <cstdarg>
#include <cstdio>

namespace cayv {

void log(std::string l, std::string fmt, ...)
{
    va_list v;
    va_start(v, fmt);

    vprintf(("[" + l + "] " + fmt + "\n").c_str(), v);

    va_end(v);
}

};
