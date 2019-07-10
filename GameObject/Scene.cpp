#include "Scene.hpp"

#include "../Physics/WorldContactListener.hpp"
#include "../Physics/PhysicsDebugDraw.hpp"
#include "../System/System.hpp"
#include <memory>
#include <cassert>

namespace wlEngine {
    void Scene::update() {
        mWorld->Step(FIXED_DELTA_TIME, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
    }



    Scene::Scene() : mWorld(new b2World(b2Vec2(0, 0))), sceneGraph() {
        //physics world
        auto collisionListener = new WorldContactListener();
        auto physicsDebugDraw = new PhysicsDebugDraw();

        mWorld->SetContactListener(collisionListener);
        mWorld->SetDebugDraw(physicsDebugDraw);

        physicsDebugDraw->SetFlags(b2Draw::e_shapeBit);
    
    }

    Scene::~Scene() {
        clearScene();
    }


    void Scene::setCamera(GameObject* newCamera) {
        this->camera = newCamera;
    }

    b2Body* Scene::createBody(b2BodyDef& def) {
        return mWorld->CreateBody(&def);
    }

    void Scene::loadScene(const std::string& filePath){
        clearScene();
        this->filePath = filePath;
		std::ifstream ifs;
		ifs.open(filePath);
		std::ostringstream oss;
		oss << ifs.rdbuf();
		ifs.close();
		sceneData.data["scene_graph"] = Json::array(); //the structure of data will be built using loadGameObjectFromJson, because createGameObject of SceneData will insert data into sceneData.data
		sceneData.data["scene_path"] = filePath;

		auto graph = nlohmann::json::parse(oss.str())["scene_graph"];
        for (auto iter = graph.begin(); iter != graph.end(); ++iter){
            loadGameObjectFromJson(*iter, nullptr); //load game object without parent para
        }
    }


    void Scene::loadGameObjectFromJson(nlohmann::json& go_json, GameObject* parent) {
        std::string name = go_json["name"];
        auto& components = go_json["components"];
        auto& children = go_json["children"];

		auto go = createGameObject(name, parent, &go_json);
        for (nlohmann::json::iterator iter = components.begin(); iter != components.end(); ++iter) {
            if (iter.key() == "Camera2D") setCamera(go);
            auto componentGenerator = (*Component::getComponentFactoryList())[std::hash<std::string>()(iter.key())];
			assert(componentGenerator != nullptr && "component is not editable!");

            auto args_json = iter.value();
            std::vector<void*> args(args_json.size());
            std::vector<std::string> arg_string(args_json.size());
            std::vector<float> arg_float(args_json.size());
            std::vector<bool> arg_bool(args_json.size());

            int i = 0;
            int argCount_string = 0;
            int argCount_float = 0;
            int argCount_bool = 0;

            for (nlohmann::json::iterator cIter = args_json.begin(); cIter != args_json.end(); ++cIter){
                if(cIter->is_string()) {
					arg_string[argCount_string] = cIter->get<std::string>(); 
                    args[i] = &arg_string[argCount_string++];
                }
                else if(cIter->is_number()) {
                    arg_float[argCount_float] = cIter->get<float>();
                    args[i] = &arg_float[argCount_float++];
                }
                else if (cIter->is_boolean()) {
                    arg_bool[argCount_bool] = cIter->get<bool>();
                    args[i] = &arg_bool[argCount_bool++];
                }
				i++;
            }
            componentGenerator(go, args.data());
        }
        
        for (nlohmann::json::iterator iter = children.begin(); iter != children.end(); ++iter) {
            loadGameObjectFromJson(*iter, go);
        }
    }

    void Scene::clearScene() {
        for (auto& k : allocatedGameObjects) {
			gameObjectAllocator.deallocate(k);
        }
        sceneGraph.clear();
        allocatedGameObjects.clear();
		sceneData.clear();
    }

    GameObject* Scene::createGameObject(const std::string& name, GameObject* parent, Json* json) {
        auto ptr = gameObjectAllocator.allocate(name);

        if (parent) {
            ptr->setParent(parent);
        }
        else {
            ptr->setParent(this);
        }
        allocatedGameObjects.insert(ptr);

#if SETTINGS_ENGINEMODE
        sceneData.createGameObject(ptr, parent, json);
#endif
        return ptr;
    }

    void Scene::destroyGameObject(GameObject* ptr) {
#if SETTINGS_ENGINEMODE
		sceneData.destroyGameObject(ptr);
#endif
		if (auto parent = ptr->getParent()) parent->children.erase(ptr);
		else sceneGraph.erase(ptr);
		allocatedGameObjects.erase(ptr);
        gameObjectAllocator.deallocate(ptr);
    }

    void Scene::addGameObject(GameObject* go){
        sceneGraph.insert(go);       
    }
    void Scene::removeGameObject(GameObject* go){
        auto parent = go->getParent();
        if (parent) {
            parent->children.erase(go);
        }
        sceneGraph.erase(go);
    }
}
