#include "EngineManager.hpp"
#include "Settings.hpp"
#include "System/RenderSystem.hpp"
#include "System/ScriptSystem.hpp"
#include "System/PhysicsSystem.hpp"
#include "System/AnimationSystem.hpp"
#include "System/UISystem.hpp"
#include "System/EventSystem.hpp"

#include "Graphics/Shader.hpp"

namespace wlEngine {
    EngineManager* EngineManager::engine = nullptr;

    EngineManager::EngineManager(){
        quit = false;
		initializeSystems();
        postInitialization();
    };

    EngineManager::~EngineManager(){};


    void EngineManager::postInitialization() {

    }

    EngineManager* EngineManager::getwlEngine() {
        if (engine) return engine;
        
        engine = new EngineManager();
        return engine;
    }

    void EngineManager::setScene(Scene* scene) {
        currentScene = scene;
    }

    void EngineManager::update() {
        currentScene->update();
    }

    void EngineManager::loop() {
        while(!quit) {
            update();
            Time::update();
        }
    }

    void EngineManager::initializeSystems() {
        Settings::init();

        RenderSystem::init();
        UISystem::init();
        AnimationSystem::init();
        ScriptSystem::init();
        PhysicsSystem::init();
        EventSystem::init();
    }
}

