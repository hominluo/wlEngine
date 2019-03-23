#include "Transform.hpp"

namespace wlEngine {
    Transform::Transform(float x, float y, float z) {
        position = glm::vec3{x,y,z};
        localPosition = glm::vec3{0, 0, 0};
    }

    Transform::Transform() {
        position = {0, 0, 0};
        localPosition = {0,0,0};
    }

    glm::vec3 Transform::getPosition() {
        return position;
    }
    
    glm::vec3 Transform::getLocalPosition() {
        return localPosition;
    }

    void Transform::moveToParent(Transform* parentTransform) {
        localPosition = position - parentTransform->position;
    }

    void Transform::setPosition(const float& x, const float& y, const float& z) {
        glm::vec3 temp{x,y,z};
        localPosition = localPosition + temp - position;
        position = temp;
    }

    void Transform::setLocalPosition(const float& x, const float& y, const float& z) {
        glm::vec3 temp{x,y,z};
        position = position + temp - localPosition;
        localPosition = temp;
    }
    
    void Transform::moveBy(const float& x, const float& y, const float& z) {
        position.x += x;
        position.y += y;
        position.z += z;

        localPosition.x += x;
        localPosition.y += y;
        localPosition.z += z;
    }
}
