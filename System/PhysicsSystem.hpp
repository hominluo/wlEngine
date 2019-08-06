#pragma once
#include "System.hpp"
#include "../Physics/WorldContactListener.hpp"
#include "../Physics/PhysicsDebugDraw.hpp"
#include <Box2D.h>

namespace wlEngine {
    class PhysicsSystem : public System {
    public:
        WorldContactListener worldContactListener;
        PhysicsDebugDraw physicsDebugDraw;
        static PhysicsSystem* get() {return system;}
        static void init();
        void update() override;
        void setUpdateBox(const float& width, const float& height, const glm::vec2& center);
    private:
        PhysicsSystem();
        static PhysicsSystem* system;

        glm::vec2 updateBoxMax;
        glm::vec2 updateBoxMin;
    };
}
