#include "Component.hpp"

namespace wlEngine {
	std::map<std::size_t, std::string>* Component::componentIdToName = getComponentIdToName();
    std::map<std::size_t, std::function<void(GameObject*, void**)>>* Component::componentFactoryList = getComponentFactoryList();
    Component::Component(GameObject* go): gameObject(go) {
        if (go == nullptr) {
            gameObjects = new std::set<GameObject*>;
        }
    }
    const std::size_t Component::componentId = std::hash<std::string>()("Component");
    bool Component::isType(const std::size_t& typeId) const {
        return Component::componentId == typeId;
    }

    std::map<std::size_t, std::function<void(GameObject*, void**)>>* Component::getComponentFactoryList() {
        if (componentFactoryList == nullptr) {
            componentFactoryList = new std::map<std::size_t, std::function<void(GameObject*, void**)>>();
        }
        return componentFactoryList;
    }

    std::size_t Component::getId() {
        return componentId;
    }

    std::size_t Component::genComponentId(const std::string& c) {
        std::size_t id = std::hash<std::string>()(c);
		(*getComponentIdToName())[id] = c;
        return id;
    }

	std::map<std::size_t, std::string>* Component::getComponentIdToName() {
		if (Component::componentIdToName == nullptr) {
			Component::componentIdToName = new std::map<std::size_t, std::string>;
		}
		return Component::componentIdToName;
	}
}

