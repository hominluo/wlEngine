#include "PhysicsSystem.hpp"
#include "../Component/TRigidbody.hpp"
#include "../Component/RigidBody.hpp"
#include "../Component/Transform.hpp"
#include "../GameObject/GameObject.hpp"

namespace wlEngine {
    PhysicsSystem* PhysicsSystem::system = nullptr;

    PhysicsSystem::PhysicsSystem() : System(), updateBoxMax(0,0), updateBoxMin(0,0) {
        registerSystem(this);
        physicsDebugDraw.SetFlags(b2Draw::e_shapeBit);
    }

    void PhysicsSystem::init() {
        if (!system) {
            system = new PhysicsSystem();
        }
    }

    void PhysicsSystem::setUpdateBox(const float& width, const float& height, const glm::vec2& center) {
        updateBoxMin = {center.x - width/2, center.y - height/2};
        updateBoxMax = {center.x + width/2, center.y + height/2};
    }

    void PhysicsSystem::update() {
        for (auto& r : RigidBody::collection) {
            auto transform = r->entity->getComponent<Transform>();
            transform->setPosition(r->getPosition());
        }
        return;
        for (auto& df : TRigidbody::dynamicFixtures) {
            auto transform = df->body->entity->getComponent<Transform>();
            //inside the box
            if (transform->position.x < updateBoxMax.x && transform->position.y < updateBoxMax.y && transform->position.x > updateBoxMin.x && transform->position.y > updateBoxMin.y) {
                
            }
        }
    }
}
