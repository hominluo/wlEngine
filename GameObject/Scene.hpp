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

            GameObject* createGameObject(const std::string& name, GameObject* parent);
			GameObject* createGameObject(const Json&, GameObject* parent);
			void addComponent(GameObject*, const Json& json);
            /**
             * @brief destroy allocated game object
             *
             * @param GameObject
             */
            void destroyGameObject(GameObject*);

            void addGameObject(GameObject*);
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
            
            /**
             * @brief load from child to parent
             *
             * @param json
             * @param id
             * @param loadedGameObjects
             *
             * @return 
             */
            GameObject* loadGameObjectFromFile(const Json& json, const std::string& id, const Json& jsonFile, std::map<std::string, GameObject*>& loadedGameObjects);

            FixedArrayAllocator<GameObject, 3000> gameObjectAllocator;

            friend FixedArrayAllocator<GameObject, 3000>;
            friend class EngineManager;
            friend class GameObject;

    };
}
