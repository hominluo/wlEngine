#ifndef SCENE_H
#define SCENE_H
#include <set>
#include <Box2D.h>
#include <glm/glm.hpp>

#include <SDL.h>

#include "GameObject.hpp"
#include "Camera.hpp"

namespace wlEngine {
    class Scene {
        public:
            Scene();
            ~Scene();
            void update();
            void addGameObject(GameObject*);
            void setCamera(Camera* camera);
            Camera* getCamera() {return camera;};
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
