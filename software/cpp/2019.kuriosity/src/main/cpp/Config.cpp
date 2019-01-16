#include "Config.h"

nlohmann::Json jsnConfig;
bool isInstantiated = false;

Config::Config(string subsystem) {
    if (not(isInstantiated)) {
        ifsConfig.reset(new std::ifstream("/lvuser/Config.json"));
        ifsConfig >> jsnConfig;
        isInstantiated = true;
    }
    _subsystem = subsystem;
}

Template<class type>
type Config::get(string key) {
    return jsnConfig[_subsystem][key];
}

Template<class type>
void Config::set(string key, type value) {
    jsnConfig[_subsystem][key] = value;
}

