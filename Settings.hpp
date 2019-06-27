#pragma once
#include <json.hpp>

using json = nlohmann::json;
namespace wlEngine {
    class Settings {
    public:
        ~Settings() {};

        static nlohmann::json settings;

        static void init();
    private:
        Settings();

    };
}
