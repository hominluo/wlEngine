#pragma once
#include "System.hpp"

namespace wlEngine {
    class PhysicsSystem : public System {
    public:
        static PhysicsSystem* get() {return system;}
        static void init();
    private:
        PhysicsSystem();
        static PhysicsSystem* system;

        void update() override;

    };
}
