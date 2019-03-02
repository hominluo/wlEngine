#include "GameObject.hpp"

namespace wlEngine {
    GameObject::GameObject(): texture(nullptr) {
         transform = new Transform(0,0,0);
    }

    void GameObject::update() {

        render();
    }
    bool GameObject::moveToParent(GameObject* parent) {
        this->parent = parent;
        transform->moveToParent(parent->transform);

        parent->children.insert(this);
        return true;
    }

    void GameObject::render() {
        if (!transform || !texture) return;
        
        const Vector3<float> position = transform->getPosition();
        texture->render(position.x, position.y);

        for (auto iter = children.begin(); iter != children.end(); iter++) {
            (*iter)->render();
        }
    }

    void GameObject::loadTexture(const char* path) {
        if (!texture) texture = new Texture();

        texture->loadFromFile(path);
    }

    void GameObject::setPosition(float x, float y, float z){
        transform->setPosition(x, y, z);
    }

    void GameObject::setLocalPosition(float x, float y, float z) {
        transform->setLocalPosition(x, y, z);
    }
}
