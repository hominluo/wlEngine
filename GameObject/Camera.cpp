#include "Camera.hpp"
#include "../Graphics/GraphicsManager.hpp"
#include "../Time.hpp"
namespace wlEngine {
    Camera::Camera() : GameObject(), perspective(true), front(0,0, -1),right(1,0,0) {
		SDL_GetMouseState(&relX, &relY);
        
    };
    Camera::~Camera() {};

	glm::mat4 Camera::getViewMatrix() {
		return glm::lookAt(transform.position, transform.position + front, glm::cross(right, front));
	}
	
    void Camera::update() {
        GameObject::update();
        updatePosition();
        if (perspective) {
            updateEyeDirection();
        }

        if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
            SDL_SetRelativeMouseMode(SDL_TRUE);
        }
        else {
            SDL_SetRelativeMouseMode(SDL_FALSE);
        }
    }
    void Camera::updateEyeDirection() {
        SDL_GetRelativeMouseState(&relX, &relY);
        yaw -= relX * sensitivity;
        pitch += relY * sensitivity;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        float yawRadians = glm::radians(yaw);
        float pitchRadians = glm::radians(pitch);
        front.x = glm::cos(yawRadians) * glm::cos(pitchRadians);
        front.y = glm::sin(pitchRadians);
        front.z = glm::sin(yawRadians) * glm::cos(pitchRadians);
        front = glm::normalize(front);
    }
    void Camera::updatePosition() {
        auto keyboard = SDL_GetKeyboardState(nullptr);
        right = glm::normalize(glm::cross(WORLD_UP, front));

        float speedDelta = speed * Time::deltaTime;
        if (keyboard[SDL_SCANCODE_LEFT]) {
            transform.position -= right * speedDelta; 
        }
        if (keyboard[SDL_SCANCODE_RIGHT]) {
            transform.position += right * speedDelta;
        }
        if (keyboard[SDL_SCANCODE_UP]) {
            transform.position += front * speedDelta;
        }
        if (keyboard[SDL_SCANCODE_DOWN]) {
            transform.position -= front * speedDelta;
        }
    }
}
