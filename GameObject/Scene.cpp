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

    void Scene::setRendererColor(const Uint8& r, const Uint8& g, const Uint8& b, const Uint8& a) {
        SDL_SetRenderDrawColor(sceneRenderer, r, g, b, a);
    }

    void Scene::loadTexture(const char* path) {
        texture.loadFromFile(path);
    }

    Scene::Scene() {
        auto graphicsManager = GraphicsManager::getGraphicsManager();
        sceneRenderer = graphicsManager->createRenderer();
    }

    Scene::~Scene() {
        GraphicsManager::getGraphicsManager()->destroyRenderer(sceneRenderer);
    }
}
