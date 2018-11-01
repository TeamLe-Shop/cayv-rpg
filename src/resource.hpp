#pragma once

#include <string>
#include <map>
#include <vector>

namespace cayv {

namespace resource {

// This is based on std::map's sorting. Lowest numerical value will come first.
// Therefore SERVER has the highest priority
enum Priority {
    BASE = 2, USER = 1, SERVER = 0
};

using ExtraInfo = std::vector<std::string>;

class Resource {
public:
    Resource();
    Resource(std::string name, std::string path, std::string type);
    Resource(std::string name, std::string path, std::string type, ExtraInfo i);

    std::string name, path, type;
    size_t extrainfo_args; // How many extra info arguments are REQUIRED.
};

class Bundle {
public:
    Bundle(std::string name, std::string path, Priority p);

    Resource* Get(std::string type, std::string name);

    std::string name, path;
    Priority priority;
    bool valid = false;
private:
    std::map<std::vector<Resource*>, std::string> resources;
};

class Manager {
public:
    Manager();

    template <typename T>
    void RegisterType(std::string tname, T dummy);
    void AddBundle(std::string path, Priority p);
    void Get(std::string type, std::string name);

private:
    std::map<Priority, Bundle> bundles;
    std::map<std::string, Resource*> types;
};

}

}
