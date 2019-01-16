#include "Json.hpp"
#include <fstream>
#include <string>

using namespace std;

class Config {
public:
    Config(string subsystem);

    template<class type>
    type get(string key);
    
    template<class type>    
    void set(string key, type value);

private:
    static std::unique_ptr<std::ifstream> ifsConfig;
    static std::unique_ptr<nlohmann::json> jsnConfig;
    string _subsystem;
    static bool isInstantiated;
};