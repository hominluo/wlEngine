#include "Camera.hpp"
#include "../Graphics/GraphicsManager.hpp"

namespace wlEngine {
    Camera::Camera() : GameObject(), perspective(true), up(0,1,0), target(0,0,0) {};
    Camera::~Camera() {};

	glm::mat4 Camera::getViewMatrix() {
		return glm::lookAt(transform.position, transform.position + glm::vec3(0,0,-1), up);
	}
	
}
