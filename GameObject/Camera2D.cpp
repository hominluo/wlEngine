#include "Camera2D.hpp"

#include "../Input.hpp"
namespace wlEngine {
    Camera2D::Camera2D(): Camera(){
        transform = addComponent<Transform>();
        transform->setPosition({0,0,5});
    };

    void Camera2D::update(){

        float speedDelta = speed * Time::deltaTime;
        if (Input::getKeyStatus(SDL_SCANCODE_LEFT)) {
            transform->position.x -= speedDelta;
        }
        if (Input::getKeyStatus(SDL_SCANCODE_RIGHT)) {
            transform->position.x +=  speedDelta;
        }
        if (Input::getKeyStatus(SDL_SCANCODE_UP)) {
            transform->position.y += speedDelta;
        }
        if (Input::getKeyStatus(SDL_SCANCODE_DOWN)) {
            transform->position.y -= speedDelta;
        }
    }

    glm::mat4 Camera2D::getViewMatrix() {
        return glm::lookAt(transform->position, transform->position + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
    }

}
