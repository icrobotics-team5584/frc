#include "Config.h"

unique_ptr<nlohmann::json> Config::jsnConfig;
unique_ptr<ifstream> Config::ifsConfig;
bool Config::isInstantiated = false;

Config::Config(string subsystem) {
    if (not(isInstantiated)) {
        ifsConfig.reset(new std::ifstream("/lvuser/config.json"));
        (*ifsConfig) >> (*jsnConfig);
        isInstantiated = true;
    }
    _subsystem = subsystem;
}

template<class type>
type Config::get(string key) {
    return (*jsnConfig)[_subsystem][key];
}

template<class type>
void Config::set(string key, type value) {
    (*jsnConfig)[_subsystem][key] = value;
}

