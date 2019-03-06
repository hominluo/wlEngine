#ifndef ENGINE_MANAGER_H
#define ENGINE_MANAGER_H
#include "Graphics/GraphicsManager.hpp"
#include "Event/EventManager.hpp"
#include "GameObject/GameObject.hpp"
#include "GameObject/Scene.hpp"

namespace wlEngine {
    class EngineManager {
        public:
            static EngineManager* getwlEngine();


            void setScene(Scene*);
            void registerEvent(const Event&);
            void unregisterEvent(const Event&);
            void loop();
            
            SDL_Renderer* getRenderer();
            ~EngineManager();

            void setQuit(const EngineEvent&);
        private:
            bool quit;

            EngineManager();
            static EngineManager* engine;

            GraphicsManager* graphicsManager;
            EventManager* eventManager;

            Scene* currentScene; 

            /* update and render the whole current scene*/
            void pollEvent();
            void update();
            void render();

            void initializeManagers();
    };
}

#endif
