#include "Transform.hpp"
#include <iostream>
namespace wlEngine {
    Transform::Transform(float x, float y, float z): position(x, y, z), rotation(1.0f) {
   
    }

    Transform::Transform() : position(0.0, 0.0, 0.0), rotation(1.0f) {
    }
    
    void Transform::moveBy(const float& x, const float& y, const float& z) {
        position.x += x;
        position.y += y;
        position.z += z;
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

}
