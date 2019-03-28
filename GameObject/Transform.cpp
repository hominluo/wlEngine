#include "Transform.hpp"

namespace wlEngine {
    Transform::Transform(float x, float y, float z) {
        position = glm::vec3{x,y,z};
    }

    Transform::Transform() {
        position = {0, 0, 0};
    }

    glm::vec3 Transform::getPosition() {
        return position;
    }
    
    void Transform::setPosition(const float& x, const float& y, const float& z) {
        glm::vec3 temp{x,y,z};
        position = temp;
    }
    
    void Transform::moveBy(const float& x, const float& y, const float& z) {
        position.x += x;
        position.y += y;
        position.z += z;
    }
}
