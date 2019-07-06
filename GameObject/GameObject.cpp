#include "GameObject.hpp"
#include "../Component/Transform.hpp"
#include "Scene.hpp"
namespace wlEngine {
    GameObject::GameObject(const std::string& name) : name(name), json_ptr(nullptr) {
        
    }

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

}
