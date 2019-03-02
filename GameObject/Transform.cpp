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

    void Transform::setPosition(float x, float y, float z) {
        Vector3<float> temp{x,y,z};
        localPosition = localPosition + temp - position;
        position = temp;
    }

    void Transform::setLocalPosition(float x, float y, float z) {
        Vector3<float> temp{x,y,z};
        position = position + temp - localPosition;
        localPosition = temp;
    }
        
}
