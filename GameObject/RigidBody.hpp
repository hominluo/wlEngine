#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <glm/vec3.hpp>
#include <Box2D.h>

namespace wlEngine {
    class RigidBody {
    public:
        RigidBody();
        ~RigidBody();

        void setGravity(bool);
        void setVelocity(const float& x, const float& y, const float& z);
        float getZMovement();

        bool getGravity();
        bool hasBody();
        /**
         * @brief update the zSpped according to z value
         *
         * @param z zSpeed is only effected by gravity if it's greater than 0
         */
        void update(const float& z);
        void setBody(b2Body* body);
        void createFixture(b2FixtureDef& def);
        glm::vec3 getPosition();
        glm::vec3 getLinearVelocity();

        /**
         * @brief called when fixtures contact begins
         */
         std::function<void()> contactBeginCallback;
         /**
          * @brief called when fixtures contact ends
          */
         std::function<void()> contactEndCallback;

    private:
        bool hasGravity;

        float zSpeed;

        b2Body* mBody; //body has to deallocated by world
    };
}

#endif
