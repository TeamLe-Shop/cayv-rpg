#pragma once

#include <string>

namespace cayv {

const std::string INFO = "INFO";
const std::string WARN = "WARN";
const std::string SEVERE = "SEVERE";

void log(std::string loglevel, std::string fmt, ...);

}
