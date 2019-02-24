#include "wlEngine.hpp"

namespace wlEngine {
    wlEngine* wlEngine::engine = nullptr;

    wlEngine::wlEngine(){
        initializeManagers();
    };

    wlEngine::~wlEngine(){};

    void wlEngine::initializeManagers() {
        GraphicsManager::initialize("Under Sky", 800, 600);
    }

    wlEngine* wlEngine::getwlEngine() {
        if (engine) return engine;
        
        engine = new wlEngine();
        return engine;
    }
}

