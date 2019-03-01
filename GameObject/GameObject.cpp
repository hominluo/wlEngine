#include "GameObject.hpp"

namespace wlEngine {
    bool GameObject::moveToParent(GameObject*) {
        for (auto iter = childs.begin(); iter != childs.end(); iter++) {
            childs.rend();
        }

        render();
        return true;
    }

    void GameObject::render() {
        const Vector3<float> position = transform->getPosition();

        texture->render(position.x, position.y);
    }
}
