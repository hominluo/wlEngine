#pragma once
#include <json.hpp>

using json = nlohmann::json;
namespace wlEngine {
#define SETTINGS_ENGINEMODE 1 // 1: editor, 0: gameplay
#define SETTINGS_GAME_DIMENSION 0 // 1: 3D, 0: 2D
    namespace Settings{
        extern enum class EngineMode : uint8_t {
            Gameplay = 0,
            Editor = 1
        } engineMode;

    }
}
