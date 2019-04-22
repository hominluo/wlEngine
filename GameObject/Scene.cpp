#include "Scene.hpp"

#include "../Graphics/GraphicsManager.hpp"
#include "../Physics/WorldContactListener.hpp"
#include "../Physics/PhysicsDebugDraw.hpp"

namespace wlEngine {
    void Scene::update() {
        mWorld->Step(FIXED_DELTA_TIME, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
        mWorld->DrawDebugData();

        if (camera) { 
            camera->update();
        }
        else assert( 0 && "No Camera Provided for Scene");
        
        for (auto iter = mGameObjects.begin(); iter != mGameObjects.end(); iter++) {
            (*iter)->update();
        }

    }

    void Scene::addGameObject(GameObject* gameObject){
        mGameObjects.insert(gameObject);
    }

    void Scene::render() {
        for (auto iter = mGameObjects.begin(); iter != mGameObjects.end(); iter++) {
            (*iter)->render();
        }
    }


    Scene::Scene() : mWorld(new b2World(b2Vec2(0, 0))) {
        auto collisionListener = new WorldContactListener();
        auto physicsDebugDraw = new PhysicsDebugDraw();

        mWorld->SetContactListener(collisionListener);
        mWorld->SetDebugDraw(physicsDebugDraw);

        physicsDebugDraw->SetFlags(b2Draw::e_shapeBit);
    
    }

    Scene::~Scene() {
    }


    void Scene::setCamera(Camera* newCamera) {
        this->camera = newCamera;
    }

    b2Body* Scene::createBody(b2BodyDef& def) {
        return mWorld->CreateBody(&def);
    }
}
