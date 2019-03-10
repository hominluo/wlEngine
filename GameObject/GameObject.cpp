#include "GameObject.hpp"

namespace wlEngine {
    GameObject::GameObject(): texture(nullptr) {

    }

    void GameObject::update() {
		for (auto iter = children.begin(); iter != children.end(); iter++) {
			(*iter)->update();
		}
	}

	bool GameObject::moveToParent(GameObject* parent) {
		this->parent = parent;
		transform.moveToParent(&parent->transform);

		parent->children.insert(this);
		return true;
	}

	void GameObject::render() {
		if (!texture) return;

		const Vector3<float> position = transform.getPosition();
		texture->render(position.x, position.y, animation.getCurrentClip());

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
        moveVector = moveVector - transform.position;

		transform.setPosition(x, y, z);

        for (auto iter = children.begin(); iter != children.end(); iter++) {
            (*iter)->moveBy(moveVector.x, moveVector.y, moveVector.z);
        }
	}

	void GameObject::setLocalPosition(const float& x, const float& y, const float& z) {
        Vector3<float> moveVector{x,y,z};
        moveVector = moveVector - transform.position;

		transform.setLocalPosition(x, y, z);

        for (auto iter = children.begin(); iter != children.end(); iter++) {
            (*iter)->moveBy(moveVector.x, moveVector.y, moveVector.z);
        }
    }

    void GameObject::moveBy(const float& x, const float& y, const float& z) {
        transform.moveBy(x, y, z);

        for (auto iter = children.begin(); iter != children.end(); iter++) {
            (*iter)->moveBy(x, y, z);
        }
    }
    void GameObject::loadClips(const char* path) {
        animation.loadClips(path);
    }

    void GameObject::playAnimation(const char* name) {
        animation.playAnimation(name);
    }
}
