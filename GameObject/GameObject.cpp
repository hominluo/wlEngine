#include "GameObject.hpp"

namespace wlEngine {
    GameObject::GameObject(): texture(nullptr), animation(nullptr) {

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

	void GameObject::render(const int& x, const int& y, const int& z) {
		if (!texture) return;

        glm::vec3 position = calculateRenderPosition(glm::vec3{x, y, z});

        auto currentClip = animation ? animation->getCurrentClip() : nullptr;
		texture->render(position.x, position.y, currentClip);

		for (auto iter = children.begin(); iter != children.end(); iter++) {
			(*iter)->render(x, y, z);
		}
	}

	void GameObject::loadTexture(const char* path) {
		if (!texture) texture = new Texture();

		texture->loadFromFile(path);
	}

	void GameObject::setPosition(const float& x, const float& y,const float& z){
        glm::vec3 moveVector{x,y,z};
        moveVector = moveVector - transform.position;

		transform.setPosition(x, y, z);

        for (auto iter = children.begin(); iter != children.end(); iter++) {
            (*iter)->moveBy(moveVector.x, moveVector.y, moveVector.z);
        }
	}

	void GameObject::setLocalPosition(const float& x, const float& y, const float& z) {
        glm::vec3 moveVector{x,y,z};
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
        if (!animation) animation = new Animation;
        animation->loadClips(path);
    }

    void GameObject::playAnimation(const char* name) {
        animation->playAnimation(name);
    }

    glm::vec3 GameObject::calculateRenderPosition(const glm::vec3& cameraPos) {
        glm::vec3 position = transform.getPosition();

        position.y = -position.y;
        position.y -= texture->getHeight();
        
        return position - cameraPos;
    }

        glm::vec3 GameObject::getPosition() {
            return transform.getPosition();
        }
        glm::vec3 GameObject::getLocalPotion() {
            return transform.getLocalPosition();
        }
}

