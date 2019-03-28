#include "Scene.hpp"

#include "../Graphics/GraphicsManager.hpp"

namespace wlEngine {
    void Scene::update() {
        mWorld->Step(FIXED_DELTA_TIME, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

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
        glm::vec3 cameraPos = camera->getPosition();

        for (auto iter = mGameObjects.begin(); iter != mGameObjects.end(); iter++) {
            (*iter)->render(cameraPos.x, cameraPos.y, cameraPos.z);
        }
    }


    Scene::Scene() : mWorld(new b2World(b2Vec2(0, 0))) {
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
