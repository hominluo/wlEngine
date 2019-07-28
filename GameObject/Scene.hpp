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
            void reloadScene();
            GameObject* getCamera() {return camera;};
            GameObject* findGameObjectByName(const std::string& name);
            b2Body* createBody(b2BodyDef& def);
			b2World* getWorld() {
				return physicsWorld;
			}
            const std::set<GameObject*>* getSceneGraph(){return &sceneGraph;};

            GameObject* createGameObject(const std::string& name, GameObject* parent);
			void addComponent(GameObject*, const Json& json);

            /**
             * @brief find the gameobject near mouse x, y
             *
             * @param mouseX
             * @param mouseY
             *
             * @return the gameobject near the position x,y in the scene window
             */
            GameObject* findGameObjectNear(const int& mouseX, const int& mouseY);
            /**
             * @brief destroy allocated game object
             *
             * @param GameObject
             */
            void destroyGameObject(GameObject*);

            void addGameObject(GameObject*);
            SceneData sceneData;
            std::string filePath;
        private:
			std::set<GameObject*> allocatedGameObjects;
			std::set<GameObject*> sceneGraph;
            GameObject* camera;
			b2World* physicsWorld;

			const float FIXED_DELTA_TIME = 1.0 / 60.0;
			const float GRAVITY = 10;

			const int32 VELOCITY_ITERATIONS = 6;
			const int32 POSITION_ITERATIONS = 2;

            //resonsible for converting z position to x and y
            void render();
            void clearScene();
			GameObject* createGameObjectByJson(const Json&, GameObject* parent);
            
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
            GameObject* findGameObjectNearHelper(std::set<GameObject*>::iterator iter, std::set<GameObject*>* set, const int&, const int&);
            GameObject* findGameObjectByNameHelper(std::set<GameObject*>::iterator iter, std::set<GameObject*>* set, const std::string& name);

            FixedArrayAllocator<GameObject, 3000> gameObjectAllocator;

            friend FixedArrayAllocator<GameObject, 3000>;
            friend class EngineManager;
            friend class GameObject;
            friend class GameEditor;

    };
}
