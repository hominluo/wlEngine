#ifndef SCENE_H
#define SCENE_H
#include <set>
#include <SDL.h>
#include <glm/vec3.hpp>

#include "../GameObject/GameObject.hpp"
#include "../GameObject/Camera.hpp"
#include "../Graphics/Texture.hpp"

namespace wlEngine {
    class Scene {
        public:
            Scene();
            ~Scene();
            void update();
            void addGameObject(GameObject*);
            void loadTexture(const char*);
            void setCamera(Camera* camera);

        private:
            Texture texture; // this texture should(can) be tiled based
            std::set<GameObject*> gameObjects;
            Camera* camera;

            //resonsible for converting z position to x and y
            void render();
            
            friend class EngineManager;
    };
}

#endif
