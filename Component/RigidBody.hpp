#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <glm/vec3.hpp>
#include <Box2D.h>
#include <functional>

#include "Component.hpp"

namespace wlEngine {
    using ContactCallbackType = std::function<void(b2Fixture* self, b2Fixture* other)>;

    class RigidBody : public Component {
        COMPONENT_DECLARATION(Component, RigidBody, 100);
    public:
        RigidBody(Entity*, b2BodyDef&);
        ~RigidBody();

        void setGravity(bool);
        void setVelocity(const float& x, const float& y, const float& z=0);
        void destroyFixture(b2Fixture*);

        bool getGravity();
        bool hasBody();
        /**
         * @brief note: the fixture user data is used to point to the Rigidbody(this) by the engine internally
         *
         * @param def
         *
         * @return 
         */
        b2Fixture* createFixture(b2FixtureDef& def);
        glm::vec3 getPosition();
        glm::vec3 getLinearVelocity();
        b2Body* getBody();

        /**
         * @brief called when fixtures contact begins
         */
         ContactCallbackType contactBeginCallback;
         /**
          * @brief called when fixtures contact ends
          */
         ContactCallbackType contactEndCallback;

    private:
        bool hasGravity;

        b2Body* body; //body has to deallocated by world
    };
}

#endif
