#include "EngineManager.hpp"
#include "System/RenderSystem.hpp"
#include "System/ScriptSystem.hpp"
#include "System/PhysicsSystem.hpp"
#include "System/AnimationSystem.hpp"
#include "System/InputSystem.hpp"
#include "System/StateMachineSystem.hpp"

#include "Graphics/Shader.hpp"
#include "Settings.hpp"

#include "Manager/ResourceManager.hpp"

namespace wlEngine {
    EngineManager* EngineManager::engine = nullptr;

    EngineManager::EngineManager(){
        quit = false;
        SDLinit();
		initializeSystems();
        initializeManagers();
        postInitialization();
    };

    void EngineManager::SDLinit() {
        if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER ) < 0) {
            std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
            exit(-1);
        }
    }

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

    void EngineManager::loop() {
#if SETTINGS_ENGINEMODE
        while (!quit) {
            if (Settings::engineMode == Settings::EngineMode::Gameplay) {
                systemUpdate();
                currentScene->update();
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
        }
#else
        while(!quit) {
            systemUpdate();
            currentScene->update();
            Time::update();
        }
#endif
    }

    void EngineManager::systemUpdate(){
        InputSystem::get()->update();
        StateMachineSystem::get()->update();
        PhysicsSystem::get()->update();
        ScriptSystem::get()->update();
        AnimationSystem::get()->update();
        RenderSystem::get()->update();
    }

    void EngineManager::initializeSystems() {
        RenderSystem::init();
        AnimationSystem::init();
        ScriptSystem::init();
        PhysicsSystem::init();
        InputSystem::init();
        StateMachineSystem::init();

    }

    void EngineManager::initializeManagers() {
        ResourceManager::init();
    }
}

