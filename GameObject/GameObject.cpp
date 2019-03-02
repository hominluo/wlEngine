#include "GameObject.hpp"

namespace wlEngine {
    void GameObject::update() {
        render();
    }
    bool GameObject::moveToParent(GameObject* parent) {
        transform->moveToParent(parent->transform);

        for (auto iter = childs.begin(); iter != childs.end(); iter++) {
            (*iter)->render();
        }

        render();
        return true;
    }

    void GameObject::render() {
        const Vector3<float> position = transform->getPosition();

        texture->render(position.x, position.y);
    }
}
