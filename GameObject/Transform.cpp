#include "Transform.hpp"

namespace wlEngine {
    Transform::Transform(float x, float y, float z) {
        position = Vector3<float>{x,y,z};
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
}
