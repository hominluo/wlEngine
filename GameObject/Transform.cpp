#include "Transform.hpp"

namespace wlEngine {
    Vector3<float> Transform::getPosition() {
        return position;
    }

    
    Transform::Transform(float x, float y, float z) {
        position = Vector3<float>{x,y,z};
    }
}
