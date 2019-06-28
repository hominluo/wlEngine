#include "Scene.hpp"

#include "../Physics/WorldContactListener.hpp"
#include "../Physics/PhysicsDebugDraw.hpp"
#include "../System/System.hpp"

namespace wlEngine {
    void Scene::update() {
        mWorld->Step(FIXED_DELTA_TIME, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

        if (camera) { 
            camera->update();
        }
        else assert( 0 && "No Camera Provided for Scene");
        
		for (auto& i : System::collection) {
			i->update();
		}

		for (auto iter = mGameObjects.begin(); iter != mGameObjects.end(); iter++) {
			(*iter)->update();
		}
    }

    void Scene::addGameObject(GameObject* gameObject){
        mGameObjects.insert(gameObject);
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
    }


    void Scene::setCamera(Camera* newCamera) {
        this->camera = newCamera;
    }

    b2Body* Scene::createBody(b2BodyDef& def) {
        return mWorld->CreateBody(&def);
    }
}
