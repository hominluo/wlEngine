#include "EngineManager.hpp"
#include "GameObject/System/RenderSystem.hpp"

namespace wlEngine {
    EngineManager* EngineManager::engine = nullptr;

    EngineManager::EngineManager(){
        quit = false;
        initializeManagers();
		initializeSystems();

        eventManager->registerEvent(Create_Event(this, &EngineManager::setQuit));
    };

    EngineManager::~EngineManager(){};

    void EngineManager::initializeManagers() {
        eventManager = EventManager::initialize();
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
        RenderSystem::init();
    }
}

