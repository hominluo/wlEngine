#include "RigidBody.hpp"
#include "../EngineManager.hpp"
namespace wlEngine {
    COMPONENT_DEFINATION(Component, RigidBody, 100);

    RigidBody::RigidBody(GameObject* go, b2BodyDef& bodyDef) : Component(go) {
        zSpeed = 0;
        contactBeginCallback = nullptr;
        contactEndCallback = nullptr;
        body = EngineManager::getwlEngine()->getCurrentScene()->createBody(bodyDef);
    };
    RigidBody::~RigidBody() {};

    void RigidBody::setGravity(bool has) {
        hasGravity = has;
    }

    void RigidBody::setVelocity(const float& x, const float& y, const float& z) {
        body->SetLinearVelocity(b2Vec2(x,y));
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

    void RigidBody::createFixture(b2FixtureDef& def) {
        auto fixture = this->body->CreateFixture(&def);
        fixture->SetUserData(this);
        
    }

    bool RigidBody::hasBody() {
        return body != nullptr;
    }

    glm::vec3 RigidBody::getPosition() {
        auto position = body->GetPosition();
        return glm::vec3(position.x, position.y, 0);
    }

    glm::vec3 RigidBody::getLinearVelocity() {
        b2Vec2 linearVelocity = body->GetLinearVelocity();
        return glm::vec3(linearVelocity.x, linearVelocity.y, zSpeed);
    }
}
