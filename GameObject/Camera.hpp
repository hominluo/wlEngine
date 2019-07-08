#pragma once
#include "GameObject.hpp"
#include <glm/matrix.hpp>

namespace wlEngine {
    class Camera : public GameObject {
    public:
		Camera() :GameObject("Camera", nullptr) {};
        virtual glm::mat4 getViewMatrix() = 0;
        virtual void update() = 0;
    };
}
