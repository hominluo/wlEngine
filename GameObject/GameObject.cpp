#include "GameObject.hpp"

namespace wlEngine {
    GameObject::GameObject(): texture(nullptr) {
         transform = new Transform(0,0,0);
    }

    void GameObject::update() {
		for (auto iter = children.begin(); iter != children.end(); iter++) {
			(*iter)->update();
		}
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

	void GameObject::setPosition(const float& x, const float& y,const float& z){
        Vector3<float> moveVector{x,y,z};
        moveVector = moveVector - transform->position;

		transform->setPosition(x, y, z);

        for (auto iter = children.begin(); iter != children.end(); iter++) {
            (*iter)->moveBy(moveVector.x, moveVector.y, moveVector.z);
        }
	}

	void GameObject::setLocalPosition(const float& x, const float& y, const float& z) {
        Vector3<float> moveVector{x,y,z};
        moveVector = moveVector - transform->position;

		transform->setLocalPosition(x, y, z);

        for (auto iter = children.begin(); iter != children.end(); iter++) {
            (*iter)->moveBy(moveVector.x, moveVector.y, moveVector.z);
        }
    }

    void GameObject::moveBy(const float& x, const float& y, const float& z) {
        transform->moveBy(x, y, z);

        for (auto iter = children.begin(); iter != children.end(); iter++) {
            (*iter)->moveBy(x, y, z);
        }
    }
}
