#pragma once
#include "GameObject.hpp"
#include <glm/matrix.hpp>

namespace wlEngine {
    class Camera : public GameObject {
    public:
        virtual glm::mat4 getViewMatrix() = 0;
        bool perspective = false;
    };
}
