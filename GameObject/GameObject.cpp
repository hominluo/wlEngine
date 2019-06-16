#include "GameObject.hpp"
#include "Component/Transform.hpp"

namespace wlEngine {
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
