#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.hpp"

namespace wlEngine {
    class Camera : public GameObject {
    public:
        Camera();
        ~Camera();

		glm::mat4 getViewMatrix();
        bool perspective;
	private:
		glm::vec3 up;
		glm::vec3 target;

    };
}

#endif
