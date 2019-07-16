#include "ScriptSystem.hpp"
#include "../Component/Script.hpp"

namespace wlEngine {
	ScriptSystem* ScriptSystem::system = nullptr;

    ScriptSystem::ScriptSystem() {
        registerSystem(this);
    }

    void ScriptSystem::update() {
        for (auto& s : Script::collection) {
            s->update();
        }
    }
    void ScriptSystem::postInit() {
        for (auto& s : Script::collection) {
            s->postInit();
        }
    }

	void ScriptSystem::init() {
		system = new ScriptSystem();
	}
}
