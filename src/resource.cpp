#include "resource.hpp"

#include "microtar.h"
#include "log.hpp"
#include "format.h"
#include "util.hpp"
#include "SDL.h"

namespace cayv {
namespace resource {

Resource::Resource(std::string n, std::string p, std::string t)
    : name(n), path(p), type(t) {}

Resource::Resource(std::string n, std::string p, std::string t, ExtraInfo i)
    : name(n), path(p), type(t) {}

Bundle::Bundle(std::string n, std::string p, Priority pr)
    : name(n), path(p), priority(pr)
{
    // TODO: Support gzip-compressed tarballs too

    mtar_t tar;
    mtar_header_t header;

    // Find the manifest
    int error;

    log(DEBUG, "Reading bundle \"{}\" from {}", n, p);

    if ((error = mtar_open(&tar, p.c_str(), "r")) != MTAR_ESUCCESS) {
        log(WARN, "Failed to open bundle {}: {}", p, mtar_strerror(error));
        return;
    }

    if ((error = mtar_find(&tar, "manifest", &header)) != MTAR_ESUCCESS) {
        log(WARN, "No manifest found in bundle ({}): {}", p,
            mtar_strerror(error));
        return;
    }

    void* buf = calloc(1, header.size + 1);

    if ((error = mtar_read_data(&tar, buf, header.size)) != MTAR_ESUCCESS) {
        log(WARN, "Couldn't read manifest in bundle ({}): {}", p,
            mtar_strerror(error));
        return;
    }

    // Sequentially read each line.

    std::string m((char*)buf);

    if (m.empty()) {
        log(WARN, "Manifest in bundle ({}) is empty", p);
        return;
    }

    size_t pos = 0;
    size_t endpos = 0;
    size_t lineno = 0;

    while ((endpos = m.find('\n', pos)) != std::string::npos) {
        pos = endpos + 1;
        if (pos >= m.size()) break;

        std::string line = trim(m.substr(pos, endpos - pos - 1));
        lineno++;
        std::string error_prefix =
            fmt::format("On line {} in manifest of bundle ({}): ", lineno, p);

        // Ignore comments/blanks
        if (line.empty() || line.substr(0, 2) == "//") continue;

        // Example definition: footstep: footstep.wav sound [any extra stuff]

        size_t colonpos = 0; // The colon separates the name from everything
                             //  else.
        if ((colonpos = line.find(':')) == std::string::npos) {
            log(WARN, error_prefix + "No colon separator found");
            continue;
        }

        std::string resource_name = line.substr(0, colonpos);
        auto args = split(line.substr(colonpos + 1, line.size()));

        if (args.size() < 2) { // Minimum requirements are path & type
            log(WARN, error_prefix + "Only {} arguments found", args.size());
            continue;
        }

        std::string resource_path = args[0], resource_type = args[1];

        log(DEBUG, "Bundle {}: Found resource \"{}\" of type {} at {}", name,
            resource_name, resource_type, resource_path);
    }

    valid = true;
}


}
}
