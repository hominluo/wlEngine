#ifndef ENGINE_MANAGER_H
#define ENGINE_MANAGER_H
#include "Graphics/GraphicsManager.hpp"
#include "GameObject/GameObject.hpp"
#include "GameObject/Scene.hpp"

namespace wlEngine {
    class EngineManager {
        public:
            static EngineManager* getwlEngine();


            void setScene(Scene*);
            void loop();
            
            SDL_Renderer* getRenderer();
            ~EngineManager();

        private:
            EngineManager();
            static EngineManager* engine;

            GraphicsManager* graphicsManager;

            Scene* currentScene; 

            /* update and render the whole current scene*/
            void update();
            void render();

            void initializeManagers();
    };
}

#endif
