#include "Transform.hpp"
#include "../GameObject/GameObject.hpp"

namespace wlEngine {
    COMPONENT_DEFINATION(Component, Transform, COMPONENT_ALLOCATION_SIZE);
	COMPONENT_EDITABLE_DEF_BEGIN(Transform) {
		float* arg0 = static_cast<float*>(args[0]);
		float* arg1 = static_cast<float*>(args[1]);
		float* arg2 = static_cast<float*>(args[2]);
		go->addComponent<Transform>(*arg0, *arg1, *arg2);
	};
	COMPONENT_EDITABLE_DEF_END(Transform);
    
    Transform::Transform(GameObject* gm) : Component(gm), position(0.0, 0.0, 0.0), rotation(1.0f), positionMat4(1.0), rotateArou(1.0), scaleMat4(1.0), scale(1.0) {
        
    }

    Transform::Transform(GameObject* gm, const float& x, const float& y, const float& z): Component(gm), position(x,y,z), rotation(1.0f), positionMat4(1.0f), rotateArou(1.0f), scaleMat4(1.0f), scale(1.0f) {
        setPosition({x,y,z});

    }
    
    void Transform::moveBy(const float& x, const float& y, const float& z) {
        position.x += x;
        position.y += y;
        position.z += z;
		
        positionMat4 = glm::translate(glm::mat4(1.0), position);

        for (auto iter = gameObject->children.begin(); iter != gameObject->children.end(); iter++) {
            auto t = (*iter)->getComponent<Transform>();
            t->moveBy(x, y, z);
        }
    }

    glm::mat4 Transform::getModel() const {
		return rotateArou * positionMat4 * rotation * scaleMat4;
    }

    void Transform::setScale(const float& x, const float& y, const float& z ) {
        scale = {x,y,z};
        scaleMat4 = glm::scale(glm::mat4(1.0), {x,y,z});              
    }
    void Transform::rotate(const glm::vec3& axis, const float& radius) {
        rotation = glm::rotate(rotation, glm::radians(radius), axis);
    }

    void Transform::setRotation(const glm::mat4& ro) {
        rotation = ro;
    }

    void Transform::rotateAround(const glm::vec3& axis, const float& radius) {
        rotateArou = glm::rotate(rotateArou, glm::radians(radius), axis);
    }

    void Transform::setPosition(const glm::vec3& pos) {
        glm::vec3 moveVector = pos - position;
        position = pos;

        positionMat4 = glm::translate(glm::mat4(1.0), position);

        for (auto iter = gameObject->children.begin(); iter != gameObject->children.end(); iter++) {
            auto t = (*iter)->getComponent<Transform>();
            if (t) t->moveBy(moveVector.x, moveVector.y, moveVector.z);
        }
    }

    void Transform::setLocalPosition(const glm::vec3& pos) {
        glm::vec3 newPosition = (gameObject->parent ? gameObject->parent->getComponent<Transform>()->getLocalPosition() : glm::vec3(0.0)) + pos;
        glm::vec3 moveVector = newPosition - position;

        position = newPosition;

        positionMat4 = glm::translate(glm::mat4(1.0), position);

        for (auto iter = gameObject->children.begin(); iter != gameObject->children.end(); iter++) {
            auto t= (*iter)->getComponent<Transform>();
            if(t)t->moveBy(moveVector.x, moveVector.y, moveVector.z);
        }
    }

    glm::vec3 Transform::getLocalPosition() {
        if (gameObject->parent) return position - gameObject->parent->getComponent<Transform>()->position;
        else return position;
    }

}
