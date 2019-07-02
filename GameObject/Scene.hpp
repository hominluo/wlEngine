#ifndef SCENE_H
#define SCENE_H
#include <set>
#include <Box2D.h>
#include <glm/glm.hpp>

#include <SDL.h>

#include "GameObject.hpp"
#include "Camera.hpp"
#include <json.hpp>
namespace wlEngine {
    class Scene {
        public:
            Scene();
            ~Scene();
            void update();
            void setCamera(Camera* camera);
            void loadScene(const nlohmann::json& scene_json);
            Camera* getCamera() {return camera;};
            b2Body* createBody(b2BodyDef& def);
			b2World* getWorld() {
				return mWorld;
			}
            const std::set<GameObject*>* getSceneGraph(){return &sceneGraph;};

            GameObject* createGameObject(std::string&& name);
            void deallocateGameObject(GameObject*);

            void addGameObject(GameObject*);
            void removeGameObject(GameObject*);
        private:
            std::set<GameObject*> allocatedGameObjects;
            std::set<GameObject*> sceneGraph;
            Camera* camera;
			b2World* mWorld;

            //resonsible for converting z position to x and y
            void render();
            void clearScene();
            void loadGameObjectFromJson(const nlohmann::json&);

            FixedArrayAllocator<GameObject, 3000> gameObjectAllocator;
            static void destoryGameObject(GameObject*);

            friend FixedArrayAllocator<GameObject, 3000>;
            friend class EngineManager;
            friend class GameObject;
    };
}

#endif
