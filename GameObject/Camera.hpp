#pragma once
#include "GameObject.hpp"
#include <glm/matrix.hpp>
#include "../Settings.hpp"
namespace wlEngine {
    class Camera : public Entity {
    public:
        Camera() :Entity("Camera") {};
        virtual glm::mat4 getViewMatrix() = 0;
        virtual void update() = 0;
    };
}
