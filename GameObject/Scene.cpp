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

        glm::vec3 cameraPos = camera->transform.getPosition();
        auto sceneTextureClip = camera->getRenderingRect();
        texture.render(0, 0, &sceneTextureClip);

        for (auto iter = gameObjects.begin(); iter != gameObjects.end(); iter++) {
            (*iter)->render(cameraPos.x, cameraPos.y, cameraPos.z);
        }
    }

    void Scene::loadTexture(const char* path) {
        texture.loadFromFile(path);
    }

    Scene::Scene() {
    }

    Scene::~Scene() {
    }


    void Scene::setCamera(Camera* newCamera) {
        newCamera->setBkgSize(texture.getWidth(), texture.getHeight());
        this->camera = newCamera;
    }
}
