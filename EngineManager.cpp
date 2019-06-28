#include "EngineManager.hpp"
#include "Settings.hpp"
#include "GameObject/System/RenderSystem.hpp"
#include "GameObject/System/ScriptSystem.hpp"
#include "GameObject/System/PhysicsSystem.hpp"
#include "GameObject/System/AnimationSystem.hpp"
#include "GameObject/System/UISystem.hpp"

#include "Graphics/Shader.hpp"

namespace wlEngine {
    EngineManager* EngineManager::engine = nullptr;

    EngineManager::EngineManager(){
        quit = false;
		initializeSystems();
        initializeManagers();
        postInitialization();

        eventManager->registerEvent(Create_Event(this, &EngineManager::setQuit));
    };

    EngineManager::~EngineManager(){};

    void EngineManager::initializeManagers() {
        eventManager = EventManager::initialize();
    }

    void EngineManager::postInitialization() {
        //Shader::collection = {{"basic_shader", new Shader()}};       
    }

    EngineManager* EngineManager::getwlEngine() {
        if (engine) return engine;
        
        engine = new EngineManager();
        return engine;
    }

    void EngineManager::setScene(Scene* scene) {
        currentScene = scene;
    }

    void EngineManager::pollEvent() {
        eventManager->pollEvent();
    }
    void EngineManager::update() {
        currentScene->update();
    }

    void EngineManager::loop() {
        while(!quit) {
            pollEvent();
            update();
            Time::update();
        }
    }

    /*Event*/
    bool EngineManager::isKeyPressed(const unsigned int& key) {
        return eventManager->isKeyPressed(key);
    }

    void EngineManager::registerEvent(const Event& e) {
        eventManager->registerEvent(e);
    }

    void EngineManager::unregisterEvent(const Event& e) {
        eventManager->unregisterEvent(e);
    }


    void EngineManager::setQuit(const EngineEvent& e) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
    }

    void EngineManager::initializeSystems() {
        Settings::init();

        RenderSystem::init();
        UISystem::init();
        AnimationSystem::init();
        ScriptSystem::init();
        PhysicsSystem::init();
    }
}

