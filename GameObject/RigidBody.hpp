#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <glm/vec3.hpp>

namespace wlEngine {
    class RigidBody {
    public:
        RigidBody();
        ~RigidBody();

        void setGravity(bool);
        void setVelocity(const float& x, const float& y, const float& z);
        glm::vec3 getVelocity();

        bool getGravity();
    private:
        bool hasGravity;

        glm::vec3 velocity;
    };
}

#endif
