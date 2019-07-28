#include "PhysicsSystem.hpp"
#include "../Component/RigidBody.hpp"
#include "../Component/Transform.hpp"
#include "../GameObject/GameObject.hpp"

namespace wlEngine {
    PhysicsSystem* PhysicsSystem::system = nullptr;

    PhysicsSystem::PhysicsSystem() : System() {
        registerSystem(this);
        physicsDebugDraw.SetFlags(b2Draw::e_shapeBit);
    }

    void PhysicsSystem::init() {
        if (!system) {
            system = new PhysicsSystem();
        }
    }

    void PhysicsSystem::update() {
        for (auto& c : RigidBody::collection) {
            auto transform = c->entity->getComponent<Transform>();
            transform->setPosition(c->getPosition());
        }
    }

}
