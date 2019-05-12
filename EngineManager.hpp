#ifndef ENGINE_MANAGER_H
#define ENGINE_MANAGER_H
#include "Event/EventManager.hpp"

#include "GameObject/System/RenderSystem.hpp"

#include "GameObject/GameObject.hpp"
#include "GameObject/Scene.hpp"
#include "Time.hpp"

namespace wlEngine {
    class EngineManager {
        public:
            static EngineManager* getwlEngine();

            void setScene(Scene*);

            /*Event*/
            void registerEvent(const Event&);
            void unregisterEvent(const Event&);
            bool isKeyPressed(const unsigned int& key);
            
            void loop();
            
            ~EngineManager();

            void setQuit(const EngineEvent&);

            Scene* getCurrentScene() {return currentScene;};
        private:
            bool quit;

            EngineManager();
            static EngineManager* engine;

            EventManager* eventManager;

            Scene* currentScene; 

            /* update and render the whole current scene*/
            void pollEvent();
            void update();

            void initializeManagers();
            void initializeSystems();
    };
}

#endif
