#include "EngineManager.hpp"
#include "System/RenderSystem.hpp"
#include "System/ScriptSystem.hpp"
#include "System/PhysicsSystem.hpp"
#include "System/AnimationSystem.hpp"
#include "System/InputSystem.hpp"

#include "Graphics/Shader.hpp"
#include "Settings.hpp"

#include "Manager/ResourceManager.hpp"

namespace wlEngine {
    EngineManager* EngineManager::engine = nullptr;

    EngineManager::EngineManager(){
        quit = false;
		initializeSystems();
        initializeManagers();
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
        systemUpdate();
        currentScene->update();
    }

    void EngineManager::loop() {
#if SETTINGS_ENGINEMODE
        while (!quit) {
            if (Settings::engineMode == Settings::EngineMode::Gameplay) {
                update();
                Time::update();
            }
            else {
                AnimationSystem::get()->update();
				if(currentScene->camera)
                RenderSystem::get()->update();
                InputSystem::get()->update();
                currentScene->update();
                Time::update();
            }
#else
            while(!quit) {
                update();
                Time::update();
            }
#endif
        }
    }

    void EngineManager::systemUpdate(){
        for (auto& i : System::collection) {
            i->update();
        }
    }

    void EngineManager::initializeSystems() {
        RenderSystem::init();
        AnimationSystem::init();
        ScriptSystem::init();
        PhysicsSystem::init();
        InputSystem::init();

    }
    
    void EngineManager::initializeManagers() {
        ResourceManager::init();
    }
}

