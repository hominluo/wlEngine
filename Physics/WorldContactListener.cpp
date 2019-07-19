#include "WorldContactListener.hpp"

namespace wlEngine {
    void WorldContactListener::BeginContact(b2Contact* contact) {
        auto rigidBodyA = static_cast<RigidBody*>(contact->GetFixtureA()->GetBody()->GetUserData());
        auto rigidBodyB = static_cast<RigidBody*>(contact->GetFixtureB()->GetBody()->GetUserData());
        if(rigidBodyA->contactBeginCallback)rigidBodyA->contactBeginCallback(rigidBodyB);
        if(rigidBodyB->contactBeginCallback)rigidBodyB->contactBeginCallback(rigidBodyA);
    }

    void WorldContactListener::EndContact(b2Contact* contact) {
        auto rigidBodyA = static_cast<RigidBody*>(contact->GetFixtureA()->GetBody()->GetUserData());
        auto rigidBodyB = static_cast<RigidBody*>(contact->GetFixtureB()->GetBody()->GetUserData());
        if(rigidBodyA->contactEndCallback)rigidBodyA->contactEndCallback(rigidBodyB);
        if(rigidBodyB->contactEndCallback)rigidBodyB->contactEndCallback(rigidBodyA);
    }
}
