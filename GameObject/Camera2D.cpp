#include "Camera2D.hpp"

namespace wlEngine {
    Camera2D::Camera2D(): Camera(){
        transform = addComponent<Transform>();
        transform->setPosition({0,0,5});
    };

    void Camera2D::update(){
        auto keyboard = SDL_GetKeyboardState(nullptr);

        float speedDelta = speed * Time::deltaTime;
        if (keyboard[SDL_SCANCODE_A]) {
            transform->position.x -= speedDelta;
        }
        if (keyboard[SDL_SCANCODE_D]) {
            transform->position.x +=  speedDelta;
        }
        if (keyboard[SDL_SCANCODE_W]) {
            transform->position.y += speedDelta;
        }
        if (keyboard[SDL_SCANCODE_S]) {
            transform->position.y -= speedDelta;
        }
    }

    glm::mat4 Camera2D::getViewMatrix() {
        return glm::lookAt(transform->position, transform->position + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
    }

}
