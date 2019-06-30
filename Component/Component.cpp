#include "Component.hpp"

namespace wlEngine {
    std::map<std::string, std::function<void(GameObject*, void*)>> Component::componentFactoryList;
    Component::Component(GameObject* go): gameObject(go) {
        if (go == nullptr) {
            gameObjects = new std::set<GameObject*>;
        }
    }
    const std::size_t Component::componentId = std::hash<std::string>()("Component");
    bool Component::isType(const std::size_t& typeId) const {
        return Component::componentId == typeId;
    }

}

