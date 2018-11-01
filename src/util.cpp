#include "util.hpp"

namespace cayv {

std::string trim(std::string s)
{
    std::string delim = " \f\n\r\t\v";
    size_t first = s.find_first_not_of(delim);
    return s.substr(first, s.find_last_not_of(delim) - first + 1);
}

std::vector<std::string> split(std::string str)
{
    std::string wstr = trim(str);
    std::vector<std::string> rv;
    size_t pos = 0, wspos = 0;
    while ((wspos = wstr.find(' ', pos)) != std::string::npos) {
        rv.push_back(wstr.substr(pos, wspos - pos));
        pos = wspos + 1;
    }

    if (pos < wstr.size() - 1) {
        rv.push_back(wstr.substr(pos));
    }

    return rv;
}

}
