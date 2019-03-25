#include "RigidBody.hpp"

namespace wlEngine {
    RigidBody::RigidBody() {};
    RigidBody::~RigidBody() {};

    void RigidBody::setGravity(bool has) {
        hasGravity = has;
    }

    void RigidBody::setVelocity(const float& x, const float& y, const float& z) {
        velocity.x = x;
        velocity.y = y;
        velocity.z = z;
    }

    glm::vec3 RigidBody::getVelocity() {
        return velocity;
    }

    bool RigidBody::getGravity() {
        return hasGravity;
    }
}
