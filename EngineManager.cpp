#include "EngineManager.hpp"

namespace wlEngine {
    EngineManager* EngineManager::engine = nullptr;

    EngineManager::EngineManager(){
        initializeManagers();
    };

    EngineManager::~EngineManager(){};

    void EngineManager::initializeManagers() {
        GraphicsManager::initialize("Under Sky", 800, 600);
        graphicsManager = GraphicsManager::getGraphicsManager();
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

    void EngineManager::render() {
        SDL_RenderClear(currentScene->sceneRenderer);
        currentScene->render();
        SDL_RenderPresent(currentScene->sceneRenderer);
    }

    void EngineManager::loop() {
        update();
        render();
    }

    SDL_Renderer* EngineManager::getRenderer() {
        return currentScene->sceneRenderer;
    }
}

