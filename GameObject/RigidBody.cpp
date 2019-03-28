#include "RigidBody.hpp"

namespace wlEngine {
    RigidBody::RigidBody() {
        zSpeed = 0;
        mBody = nullptr;
    };
    RigidBody::~RigidBody() {};

    void RigidBody::setGravity(bool has) {
        hasGravity = has;
    }

    void RigidBody::setVelocity(const float& x, const float& y, const float& z) {
        if (mBody) {
            mBody->SetLinearVelocity(b2Vec2(x,y));
        }
        zSpeed = z;
    }

    float RigidBody::getZMovement() {
        return zSpeed * FIXED_DELTA_TIME;
    }

    bool RigidBody::getGravity() {
        return hasGravity;
    }

    void RigidBody::update(const float& z) {
        if (z > 0) zSpeed -= GRAVITY * FIXED_DELTA_TIME;
        else {
            zSpeed = 0 ;
        }

    }

    void RigidBody::setBody(b2Body* body) {
        this->mBody = body;
    }

    void RigidBody::createFixture(b2FixtureDef& def) {
        this->mBody->CreateFixture(&def);
    }

    bool RigidBody::hasBody() {
        return mBody != nullptr;
    }

    glm::vec3 RigidBody::getPosition() {
        auto position = mBody->GetPosition();
        return glm::vec3(position.x, position.y, 0);
    }
}
