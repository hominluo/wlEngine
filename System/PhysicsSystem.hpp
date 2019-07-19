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
    private:
        PhysicsSystem();
        static PhysicsSystem* system;

        void update() override;


    };
}
