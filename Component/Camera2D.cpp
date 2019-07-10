#include "Camera2D.hpp"
#include "../GameObject/GameObject.hpp"
#include "../Input.hpp"
#include "../Time.hpp"
namespace wlEngine {
    COMPONENT_DEFINATION(Component, Camera2D, 3);
    COMPONENT_EDITABLE_DEF_BEGIN(Camera2D) {
        go->addComponent<Camera2D>();
    };
    COMPONENT_EDITABLE_DEF_END(Camera2D);

    Camera2D::Camera2D(GameObject* go) : Component(go) {}

    glm::mat4 Camera2D::getViewMatrix() {
        if (!transform) transform=gameObject->getComponent<Transform>();

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
        return glm::lookAt(transform->position, transform->position + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
    }

}
