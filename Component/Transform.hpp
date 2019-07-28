#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Component.hpp"

#define COMPONENT_ALLOCATION_SIZE 1000
namespace wlEngine {
    class Entity;
    class Transform : public Component {
        COMPONENT_DECLARATION(Component, Transform, COMPONENT_ALLOCATION_SIZE);
        COMPONENT_EDITABLE_DEC();
    public:
        Transform(Entity*);
        Transform(Entity*, const float& x, const float& y, const float& z);
        Transform(Entity*, const glm::vec3&);
        Transform(Entity*, void** data);

        glm::vec3 position;
        glm::mat4 positionMat4;
        glm::mat4 rotation;
        glm::mat4 rotateArou;
        glm::mat4 scaleMat4;

        glm::vec3 scale;

        void moveBy(const float& x, const float& y, const float& z);
        void setPosition(const glm::vec3& pos);
        void setLocalPosition(const glm::vec3& pos);
        glm::vec3 getLocalPosition();

        void rotate(const glm::vec3& axis, const float& radius);
        void setRotation(const glm::mat4& ro);
        void setScale(const float& x, const float& y, const float& z);
        void rotateAround(const glm::vec3& axis, const float& radius);
        glm::mat4 getModel() const ;

    private:
        friend class Entity;
    };
}

#endif
