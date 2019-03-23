#include "Scene.hpp"

#include "../Graphics/GraphicsManager.hpp"

namespace wlEngine {
    void Scene::update() {
        if (camera) { 
            camera->update();
        }
        else assert( 0 && "No Camera Provided for Scene");
        
        for (auto iter = gameObjects.begin(); iter != gameObjects.end(); iter++) {
            (*iter)->update();
        }

    }

    void Scene::addGameObject(GameObject* gameObject){
        gameObjects.insert(gameObject);
    }

    void Scene::render() {
        glm::vec3 cameraPos = camera->getPosition();

        for (auto iter = gameObjects.begin(); iter != gameObjects.end(); iter++) {
            (*iter)->render(cameraPos.x, cameraPos.y, cameraPos.z);
        }
    }


    Scene::Scene() {
    }

    Scene::~Scene() {
    }


    void Scene::setCamera(Camera* newCamera) {
        this->camera = newCamera;
    }
}
