#include "Transform.hpp"

namespace wlEngine {
    Transform::Transform(float x, float y, float z) {
        position = Vector3<float>{x,y,z};
        localPosition = Vector3<float>{0, 0, 0};
    }

    Vector3<float> Transform::getPosition() {
        return position;
    }
    
    Vector3<float> Transform::getLocalPosition() {
        return localPosition;
    }

    void Transform::moveToParent(Transform* parentTransform) {
        localPosition = position - parentTransform->position;
    }

    void Transform::setPosition(const float& x, const float& y, const float& z) {
        Vector3<float> temp{x,y,z};
        localPosition = localPosition + temp - position;
        position = temp;
    }

    void Transform::setLocalPosition(const float& x, const float& y, const float& z) {
        Vector3<float> temp{x,y,z};
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
