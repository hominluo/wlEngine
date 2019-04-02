#include "WorldContactListener.hpp"

namespace wlEngine {
    void WorldContactListener::BeginContact(b2Contact* contact) {
        auto fixtureA = contact->GetFixtureA();
        auto fixtureB = contact->GetFixtureB();

        auto dataA = fixtureA->GetUserData();
        auto dataB = fixtureB->GetUserData();

        if (dataA) {
            auto rigidBodyA = static_cast<RigidBody*>(dataA);
            auto callback = rigidBodyA->contactBeginCallback;

            if (callback) callback();
            
        }

        if (dataB) {
            auto rigidBodyB = static_cast<RigidBody*>(dataB);
            auto callback = rigidBodyB->contactBeginCallback;

            if (callback) callback();

        }
    }

    void WorldContactListener::EndContact(b2Contact* contact) {

        auto fixtureA = contact->GetFixtureA();
        auto fixtureB = contact->GetFixtureB();

        auto dataA = fixtureA->GetUserData();
        auto dataB = fixtureB->GetUserData();

        if (dataA) {
            auto rigidBodyA = static_cast<RigidBody*>(dataA);
            auto callback = rigidBodyA->contactBeginCallback;

            if (callback) callback();

        }

        if (dataB) {
            auto rigidBodyB = static_cast<RigidBody*>(dataB);
            auto callback = rigidBodyB->contactBeginCallback;

            if (callback) callback();

        }
    }
}
