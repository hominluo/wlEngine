#include "ScriptSystem.hpp"
#include "../Component/Script.hpp"

namespace wlEngine {
    ScriptSystem::ScriptSystem() {
        registerSystem(this);
    }

    void ScriptSystem::update() {
        for (auto& s : Script::collection) {
            s->update();
        }
    }
}
