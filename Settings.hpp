#pragma once
#include <json.hpp>

using json = nlohmann::json;
namespace wlEngine {
#define SETTINGS_ENGINEMODE 1 // 1: editor, 0: gameplay
    namespace Settings{
        extern enum class GameDimension : uint8_t {
            Dimension2D = 0,
            Dimension3D = 1
        } gameDimension;

        extern enum class EngineMode : uint8_t {
            Gameplay = 0,
            Editor = 1
        } engineMode;

    }
}
