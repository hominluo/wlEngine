#include "Camera.hpp"
#include "../Graphics/GraphicsManager.hpp"

namespace wlEngine {
    Camera::Camera() : GameObject() {};
    Camera::~Camera() {};

    glm::vec3 Camera::getPosition() {
        auto position = GameObject::getPosition();

        auto graphicsManager = GraphicsManager::getGraphicsManager();

        position.y = -position.y;
        position.y -= graphicsManager->getWindowHeight();

        return position;
    }

}
