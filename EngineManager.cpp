#include "EngineManager.hpp"

namespace wlEngine {
    EngineManager* EngineManager::engine = nullptr;

    EngineManager::EngineManager(){
        quit = false;
        initializeManagers();

        eventManager->registerEvent(Create_Event(this, &EngineManager::setQuit));
    };

    EngineManager::~EngineManager(){};

    void EngineManager::initializeManagers() {
        graphicsManager = GraphicsManager::initialize("Under Sky", 800, 600);

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

    void EngineManager::render() {
        SDL_RenderClear(currentScene->sceneRenderer);
        currentScene->render();
        SDL_RenderPresent(currentScene->sceneRenderer);
    }

    void EngineManager::loop() {
/*this design looks wrong, I am not sure. 
 * Think about character controling. 
 * the movement is updated before the call of update */
        while(!quit) {
            pollEvent();
            update();
            render();
        }
    }

    SDL_Renderer* EngineManager::getRenderer() {
        return currentScene->sceneRenderer;
    }

    /*Event*/
    bool EngineManager::isKeyPressed(const uint& key) {
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
}

