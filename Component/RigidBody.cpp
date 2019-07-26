#include "RigidBody.hpp"
#include "../EngineManager.hpp"
namespace wlEngine {
    COMPONENT_DEFINATION(Component, RigidBody, 100);

    RigidBody::RigidBody(GameObject* go, b2BodyDef& bodyDef) : Component(go) {
		assert(bodyDef.userData == nullptr && "body shouldn't carry user defined data, it's used by the engine. Try using fixture's user data instead");
        contactBeginCallback = nullptr;
        contactEndCallback = nullptr;
        body = EngineManager::getwlEngine()->getCurrentScene()->createBody(bodyDef);
        body->SetUserData(this);
    };

    RigidBody::~RigidBody() {
        body->GetWorld()->DestroyBody(body);
    };

    void RigidBody::setGravity(bool has) {
        hasGravity = has;
    }

    void RigidBody::setVelocity(const float& x, const float& y, const float& z) {
        body->SetLinearVelocity(b2Vec2(x,y));
    }

    bool RigidBody::getGravity() {
        return hasGravity;
    }


    b2Fixture* RigidBody::createFixture(b2FixtureDef& def) {
        return this->body->CreateFixture(&def);
    }

    b2Body* RigidBody::getBody() {
        return body;
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
        return glm::vec3(linearVelocity.x, linearVelocity.y, 0);
    }

    void RigidBody::destroyFixture(b2Fixture* fixture) {
        body->DestroyFixture(fixture);
    }
}
