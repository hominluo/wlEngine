#pragma once
#include <set>
#include <Box2D.h>
#include <glm/glm.hpp>

#include <SDL.h>

#include "GameObject.hpp"
#include "../GameEditor/SceneData.hpp"
#include <json.hpp>
namespace wlEngine {
    class Scene {
        public:
            Scene();
            ~Scene();
            void update();
            void setCamera(GameObject* camera);
			void loadScene(const std::string& path);
            GameObject* getCamera() {return camera;};
            b2Body* createBody(b2BodyDef& def);
			b2World* getWorld() {
				return mWorld;
			}
            const std::set<GameObject*>* getSceneGraph(){return &sceneGraph;};;

            GameObject* createGameObject(const std::string& name, GameObject* parent, nlohmann::json*);
            void destroyGameObject(GameObject*);

            void addGameObject(GameObject*);
            void removeGameObject(GameObject*);

#if SETTINGS_ENGINEMODE
            SceneData sceneData;
#endif
            std::string filePath;
        private:
			std::set<GameObject*> allocatedGameObjects;
			std::set<GameObject*> sceneGraph;
            GameObject* camera;
			b2World* mWorld;

            //resonsible for converting z position to x and y
            void render();
            void clearScene();
            void loadGameObjectFromJson(nlohmann::json&, GameObject* parent);

            FixedArrayAllocator<GameObject, 3000> gameObjectAllocator;

            friend FixedArrayAllocator<GameObject, 3000>;
            friend class EngineManager;
            friend class GameObject;

    };
}
