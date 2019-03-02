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
        SDL_RenderClear(currentScene->sceneRenderer);
        GameObject();
        currentScene->update();
        SDL_RenderPresent(currentScene->sceneRenderer);
    }

    SDL_Renderer* EngineManager::getRenderer() {
        return currentScene->sceneRenderer;
    }
}

