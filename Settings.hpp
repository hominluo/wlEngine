#pragma once
#include <json.hpp>

using json = nlohmann::json;
namespace wlEngine {
#define SETTINGS_ENGINEMODE 1
    namespace Settings{
        extern enum class GameDimension : uint8_t {
            Dimension2D = 0,
            Dimension3D = 1
        } gameDimension;

    }
}
