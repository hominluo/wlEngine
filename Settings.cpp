#include "Settings.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
namespace wlEngine {
    namespace Settings {
#if SETTINGS_ENGINEMODE
        EngineMode engineMode = EngineMode::Editor;
#else
        EngineMode engineMode = EngineMode::Gameplay;
#endif
    }
}
