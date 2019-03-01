#include "EngineManager.hpp"

namespace wlEngine {
    EngineManager* EngineManager::engine = nullptr;

    EngineManager::EngineManager(){
        initializeManagers();
    };

    EngineManager::~EngineManager(){};

    void EngineManager::initializeManagers() {
        GraphicsManager::initialize("Under Sky", 800, 600);
    }

    EngineManager* EngineManager::getwlEngine() {
        if (engine) return engine;
        
        engine = new EngineManager();
        return engine;
    }
}

