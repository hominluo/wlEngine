#ifndef ENGINE_MANAGER_H
#define ENGINE_MANAGER_H
#include "Graphics/GraphicsManager.hpp"
#include "GameObject/GameObject.hpp"
#include "GameObject/Scene.hpp"

namespace wlEngine {
    class EngineManager {
        public:
            static EngineManager* getwlEngine();

            /* update the whole game*/
            void update();

            void setScene(Scene*);
            
            SDL_Renderer* getRenderer();
            ~EngineManager();

        private:
            EngineManager();
            static EngineManager* engine;

            GraphicsManager* graphicsManager;

            Scene* currentScene; 

            void initializeManagers();
    };
}

#endif
