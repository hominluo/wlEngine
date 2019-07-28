#pragma once
#include "Component.hpp"
#include <glm/matrix.hpp>
#include "Transform.hpp"
namespace wlEngine {
    struct CoordTransform {
        glm::mat4 view; 
        glm::mat4 projection;// 
    };

    struct Camera2D : Component {
        COMPONENT_DECLARATION(Component, Camera2D, 3);
        COMPONENT_EDITABLE_DEC();
    public:
        Camera2D(Entity* go);
		Camera2D(Entity* go, void**) : Camera2D(go){};
        const CoordTransform& getTransformMatrix();
        float speed = 100.0;
        Transform* transform = nullptr;
    private:
        CoordTransform coordTransform;
        glm::vec2 viewport;
        float viewportScale;
    };
}
