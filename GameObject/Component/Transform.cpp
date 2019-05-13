#include "Transform.hpp"
#include "../GameObject.hpp"

namespace wlEngine {
    COMPONENT_DEFINATION(Component, Transform, COMPONENT_ALLOCATION_SIZE);
    
    Transform::Transform(GameObject* gm) : Component(gm), position(0.0, 0.0, 0.0), rotation(1.0f) {
    }
    
    void Transform::moveBy(const float& x, const float& y, const float& z) {
        position.x += x;
        position.y += y;
        position.z += z;

        for (auto iter = gameObject->children.begin(); iter != gameObject->children.end(); iter++) {
            (*iter)->getComponent<Transform>()->moveBy(x, y, z);
        }
    }

    glm::mat4 Transform::getModel() const {
		return glm::translate(glm::mat4(1.0f), position) * rotation;
    }

    void Transform::rotate(const glm::vec3 axis, const float& radius) {
        rotation = glm::rotate(rotation, glm::radians(radius), axis);
    }

    void Transform::setRotation(const glm::mat4& ro) {
        rotation = ro;
    }

    void Transform::setPosition(const glm::vec3& pos) {
        glm::vec3 moveVector = pos - position;
        position = pos;

        for (auto iter = gameObject->children.begin(); iter != gameObject->children.end(); iter++) {
            (*iter)->getComponent<Transform>()->moveBy(moveVector.x, moveVector.y, moveVector.z);
        }
    }

    void Transform::setLocalPosition(const glm::vec3& pos) {
        glm::vec3 newPosition = gameObject->parent->getComponent<Transform>()->position + pos;
        glm::vec3 moveVector = newPosition - position;

		position = pos;

        for (auto iter = gameObject->children.begin(); iter != gameObject->children.end(); iter++) {
            (*iter)->getComponent<Transform>()->moveBy(moveVector.x, moveVector.y, moveVector.z);
        }
    }

    glm::vec3 Transform::getLocalPosition() {
        if (gameObject->parent) return position - gameObject->parent->getComponent<Transform>()->position;
        else return position;
    }
}
