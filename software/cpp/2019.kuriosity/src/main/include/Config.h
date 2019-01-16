#include "Json.h"
#include <fstream>

class Config {

public:
    Config(string subsystem);

    Template<class type>
    type get(string key);
    
    Template<class type>    
    void set(string key, type value);

private:
    static std::unique_ptr<std::ifstream> ifsConfig;
    static std::unique_ptr<nlohmann::Json> jsnConfig;
    static bool isInstantiated = false;
    string _subsystem;
}