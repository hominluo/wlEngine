#include "GameObject.hpp"
#include "../Component/Transform.hpp"
#include "Scene.hpp"
#include "../EngineManager.hpp"
namespace wlEngine {
    GameObject::GameObject(const std::string& name) : name(name) {}

    void GameObject::setParent(GameObject* newParent) {
        //remove from previous hierachy
        if (auto preParent = this->parent) preParent->children.erase(this);
        else {
            EngineManager::getwlEngine()->getCurrentScene()->sceneGraph.erase(this);
        }
        
        //add to new hierachy
        if(newParent) {
            this->parent = newParent;
            newParent->children.insert(this);
        }
        else {
            EngineManager::getwlEngine()->getCurrentScene()->sceneGraph.insert(this);
            this->parent = nullptr;
        }
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
