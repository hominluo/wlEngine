#ifndef ENGINE_MANAGER_H
#define ENGINE_MANAGER_H

#include "System/RenderSystem.hpp"

#include "GameObject/GameObject.hpp"
#include "GameObject/Scene.hpp"
#include "Time.hpp"

namespace wlEngine {
    class EngineManager {
        public:
            static EngineManager* getwlEngine();

            void setScene(Scene*);

            
            void loop();
            
            ~EngineManager();


            Scene* getCurrentScene() {return currentScene;};
        private:
            bool quit;

            EngineManager();
            static EngineManager* engine;

            Scene* currentScene; 

            void update();

            void initializeSystems();

            /**
             * @brief initialize anything that needs systemt to set up first
             */
            void postInitialization();

            void systemUpdate();
    };
}

#endif
