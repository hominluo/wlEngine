#pragma once
#include "GameObject.hpp"
#include <glm/matrix.hpp>

namespace wlEngine {
    class Camera : public GameObject {
    public:
		Camera() :GameObject("Camera") {};
        virtual glm::mat4 getViewMatrix() = 0;
    };
}
