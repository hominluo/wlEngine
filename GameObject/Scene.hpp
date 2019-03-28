#ifndef SCENE_H
#define SCENE_H
#include <set>
#include <SDL.h>
#include <Box2D.h>
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
            void setCamera(Camera* camera);
            b2Body* createBody(b2BodyDef& def);

        private:
            std::set<GameObject*> mGameObjects;
            Camera* camera;
            b2World* mWorld;

            //resonsible for converting z position to x and y
            void render();
            
            friend class EngineManager;
    };
}

#endif
