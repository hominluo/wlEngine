#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace wlEngine {
    class GameObject;
    class Transform {
        //no rotaion and flip yet
    public:
		glm::vec3 position;
		
        Transform(GameObject*);

        void moveBy(const float& x, const float& y, const float& z);
        void setPosition(const glm::vec3& pos);
        void setLocalPosition(const glm::vec3& pos);
        glm::vec3 getLocalPosition();

		void rotate(const glm::vec3 axis, const float& radius);
		void setRotation(const glm::mat4& ro);
		glm::mat4 getModel() const ;
	private:
		glm::mat4 rotation;
        GameObject* gameObject;
    };
}

#endif
