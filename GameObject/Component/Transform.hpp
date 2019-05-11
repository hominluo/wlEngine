#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Component.hpp"

#define COMPONENT_ALLOCATION_SIZE 1000
namespace wlEngine {
    class GameObject;
    struct Transform : public Component {
		COMPONENT_DECLARATION(Component, Transform, COMPONENT_ALLOCATION_SIZE);
        Transform(GameObject*);

		glm::vec3 position;
		glm::mat4 rotation;

        void moveBy(const float& x, const float& y, const float& z);
        void setPosition(const glm::vec3& pos);
        void setLocalPosition(const glm::vec3& pos);
        glm::vec3 getLocalPosition();

		void rotate(const glm::vec3 axis, const float& radius);
		void setRotation(const glm::mat4& ro);
		glm::mat4 getModel() const ;
    };
}

#endif