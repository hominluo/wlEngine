#pragma once
#include "Component.hpp"
#include <glm/matrix.hpp>
#include "Transform.hpp"
namespace wlEngine {
    struct Camera2D : Component {
        COMPONENT_DECLARATION(Component, Camera2D, 3);
        COMPONENT_EDITABLE_DEC();
    public:
        Camera2D(GameObject* go);
        glm::mat4 getViewMatrix();
        float speed = 100.0;
        Transform* transform = nullptr;
    };
}
