#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

class GameObject;
namespace wlEngine {
    //TO_DO: There should be a actual position and rendering position
    //user sets the actual position, Transform calculates the rendering
    //position for Z
    class Transform {
        //no rotaion and flip yet
    public:
		glm::vec3 position;
		
        Transform(float x, float y, float z);
        Transform();

        void moveBy(const float& x, const float& y, const float& z);
		void rotate(const glm::vec3 axis, const float& radius);
		void setRotation(const glm::mat4& ro);
		glm::mat4 getModel() const ;
	private:
		glm::mat4 rotation;
        GameObject* gameObject;
    };
}

#endif
