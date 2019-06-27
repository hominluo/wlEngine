#include "Settings.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
namespace wlEngine {
    nlohmann::json Settings::settings;

    void Settings::init() {
        std::ifstream ifs;
        ifs.open("../wlEngine/settings.json");

        if(ifs.good()) {
            std::ostringstream oss;

            oss << ifs.rdbuf();
            settings = json::parse(oss.str());

        }
        else {
            std::cerr << "settings read error!";
        }

        ifs.close();
    }

    Settings::Settings(){}
}
