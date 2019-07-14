#include "Scene.hpp"

#include "../Physics/WorldContactListener.hpp"
#include "../Physics/PhysicsDebugDraw.hpp"
#include "../System/System.hpp"
#include "../Utility/Utility.hpp"
#include <memory>
#include <cassert>

namespace wlEngine {
    void Scene::update() {
        mWorld->Step(FIXED_DELTA_TIME, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
    }



    Scene::Scene() : mWorld(new b2World(b2Vec2(0, 0))), sceneGraph(), gameObjectAllocator(){
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
		sceneData.data = Json::object(); //the structure of data will be built using loadGameObjectFromJson, because createGameObject of SceneData will insert data into sceneData.data
		sceneData.data["scene_path"] = filePath;

        Json gameObjects_json = nlohmann::json::parse(oss.str())["gameObjects"];
		std::map<std::string, GameObject*> loadedGameObjects;
        for (auto iter = gameObjects_json.begin(); iter != gameObjects_json.end(); ++iter){
            loadGameObjectFromFile(iter.value(), iter.key(), gameObjects_json, loadedGameObjects);
        }
    }

    GameObject* Scene::loadGameObjectFromFile(const Json& go_json, const std::string& id, const Json& jsonFile, std::map<std::string, GameObject*>& loadedGameObjects) {
		//avoid recreation
		if (loadedGameObjects.find(id) != loadedGameObjects.end()) return loadedGameObjects[id];
		std::string name = go_json["name"];
		auto& components = go_json["components"];
		auto parent_id = go_json["parent"].get<std::string>();

        //allocate parent gameObject
        GameObject* parent = nullptr;
		if(parent_id != Utility::toPointerString(parent)) parent = loadGameObjectFromFile(jsonFile[parent_id], parent_id, jsonFile, loadedGameObjects);

        //create gameObject with the parent
		auto go = createGameObject(name, parent);
		addComponent(go, components);

		sceneData.createGameObject(go, parent, &go_json);
        loadedGameObjects[id] = go;
        return go;
    }

    void Scene::addComponent(GameObject* go, const Json& components) {
        for (nlohmann::json::const_iterator iter = components.begin(); iter != components.end(); ++iter) {
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
    }

    GameObject* Scene::createGameObject(const Json& go_json, GameObject* parent) {
        std::string name = go_json["name"];
        auto& components = go_json["components"];
        auto& children = go_json["children"];

        auto go = createGameObject(name, parent);
        addComponent(go, components);

        sceneData.createGameObject(go, parent, &go_json);

        for(Json::const_iterator iter = children.begin(); iter != children.end(); ++iter) {
            createGameObject(sceneData.data[iter->get<std::string>()], go);
        }
		return go;
    }

    void Scene::clearScene() {
        for (auto& k : allocatedGameObjects) {
            gameObjectAllocator.deallocate(k);
        }
        sceneGraph.clear();
        allocatedGameObjects.clear();
        sceneData.clear();
    }

    GameObject* Scene::createGameObject(const std::string& name, GameObject* parent) {
        auto ptr = gameObjectAllocator.allocate(name);

        if (parent) ptr->setParent(parent);
        else ptr->setParent(this);

        allocatedGameObjects.insert(ptr);
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
}
