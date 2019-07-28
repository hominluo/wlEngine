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
            void setCamera(Entity* camera);
			void loadScene(const std::string& path);
            void reloadScene();
            Entity* getCamera() {return camera;};
            Entity* findGameObjectByName(const std::string& name);
            b2Body* createBody(b2BodyDef& def);
			b2World* getWorld() {
				return physicsWorld;
			}
            const std::set<Entity*>* getSceneGraph(){return &sceneGraph;};

            Entity* createGameObject(const std::string& name, Entity* parent);
			void addComponent(Entity*, const Json& json);

            /**
             * @brief find the gameobject near mouse x, y
             *
             * @param mouseX
             * @param mouseY
             *
             * @return the gameobject near the position x,y in the scene window
             */
            Entity* findGameObjectNear(const int& mouseX, const int& mouseY);
            /**
             * @brief destroy allocated game object
             *
             * @param GameObject
             */
            void destroyGameObject(Entity*);

            void addGameObject(Entity*);
            SceneData sceneData;
            std::string filePath;
        private:
			std::set<Entity*> allocatedGameObjects;
			std::set<Entity*> sceneGraph;
            Entity* camera;
			b2World* physicsWorld;

			const float FIXED_DELTA_TIME = 1.0 / 60.0;
			const float GRAVITY = 10;

			const int32 VELOCITY_ITERATIONS = 6;
			const int32 POSITION_ITERATIONS = 2;

            //resonsible for converting z position to x and y
            void render();
            void clearScene();
			Entity* createGameObjectByJson(const Json&, Entity* parent);
            
            /**
             * @brief load from child to parent
             *
             * @param json
             * @param id
             * @param loadedGameObjects
             *
             * @return 
             */
            Entity* loadGameObjectFromFile(const Json& json, const std::string& id, const Json& jsonFile, std::map<std::string, Entity*>& loadedGameObjects);
            Entity* findGameObjectNearHelper(std::set<Entity*>::iterator iter, std::set<Entity*>* set, const int&, const int&);
            Entity* findGameObjectByNameHelper(std::set<Entity*>::iterator iter, std::set<Entity*>* set, const std::string& name);

            FixedArrayAllocator<Entity, 3000> gameObjectAllocator;

            friend FixedArrayAllocator<Entity, 3000>;
            friend class EngineManager;
            friend class Entity;
            friend class GameEditor;

    };
}
