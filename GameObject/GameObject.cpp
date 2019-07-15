#include "GameObject.hpp"
#include "../Component/Transform.hpp"
#include "Scene.hpp"
#include "../EngineManager.hpp"
namespace wlEngine {
    GameObject::GameObject(const std::string& name) : name(name) {}

    void GameObject::setParent(Scene* scene) {
        scene->addGameObject(this);       
    }
    void GameObject::setParent(GameObject* go) {
        parent = go;
        go->children.insert(this);
    }

    GameObject::~GameObject() {
        for(auto& c : components) {
            c->destruct(this);
        }
    }

    void GameObject::removeComponent(Component* component) {
        for(auto c : components) {
            if(c.get() == component) {
                if(c->gameObjects) {
                    c->gameObjects->erase(this);
                }
                components.erase(c);
                return;
            }
        }
    }

}
