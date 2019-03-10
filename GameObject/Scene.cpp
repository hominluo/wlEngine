#include "Scene.hpp"

#include "../Graphics/GraphicsManager.hpp"

namespace wlEngine {
    void Scene::update() {

        for (auto iter = gameObjects.begin(); iter != gameObjects.end(); iter++) {
            (*iter)->update();
        }

    }

    void Scene::addGameObject(GameObject* gameObject){
        gameObjects.insert(gameObject);
    }

    void Scene::render() {
        texture.render(0, 0);

        for (auto iter = gameObjects.begin(); iter != gameObjects.end(); iter++) {
            (*iter)->render();
        }
    }

    void Scene::loadTexture(const char* path) {
        texture.loadFromFile(path);
    }

    Scene::Scene() {
    }

    Scene::~Scene() {
    }
}
