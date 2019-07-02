#include "Scene.hpp"

#include "../Physics/WorldContactListener.hpp"
#include "../Physics/PhysicsDebugDraw.hpp"
#include "../System/System.hpp"
#include <memory>

namespace wlEngine {
    void Scene::update() {
        mWorld->Step(FIXED_DELTA_TIME, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
    }



    Scene::Scene() : mWorld(new b2World(b2Vec2(0, 0))) {
        //physics world
        auto collisionListener = new WorldContactListener();
        auto physicsDebugDraw = new PhysicsDebugDraw();

        mWorld->SetContactListener(collisionListener);
        mWorld->SetDebugDraw(physicsDebugDraw);

        physicsDebugDraw->SetFlags(b2Draw::e_shapeBit);
    
        //system
        
    }

    Scene::~Scene() {
        clearScene();
    }


    void Scene::setCamera(Camera* newCamera) {
        this->camera = newCamera;
    }

    b2Body* Scene::createBody(b2BodyDef& def) {
        return mWorld->CreateBody(&def);
    }

    void Scene::loadScene(const nlohmann::json& scene_json){
        clearScene();

        auto graph = scene_json["scene_graph"];
    }


    void Scene::loadGameObjectFromJson(const nlohmann::json& go_json) {

    }

    void Scene::clearScene() {
        for (auto& k : allocatedGameObjects) {
            deallocateGameObject(k);
        }
    }

    GameObject* Scene::createGameObject(std::string&& name) {
        auto ptr = gameObjectAllocator.allocate(name);
        allocatedGameObjects.insert(ptr);
        return ptr;
    }

    void Scene::deallocateGameObject(GameObject* ptr) {
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
