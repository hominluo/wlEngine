#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace wlEngine {
    class Camera : public GameObject {
    public:
        Camera();
        ~Camera();

		glm::mat4 getViewMatrix();
        void update() override;
        bool perspective;

    protected:
        glm::vec3 front;
        glm::vec3 right;
        const glm::vec3 WORLD_UP = glm::vec3(0,1,0);

        //mouse
        int relX;
        int relY;
        float sensitivity = 0.3;

        float pitch = 0;
        float yaw = -90;

        float speed = 30;
    private:
        void updateEyeDirection();
        void updatePosition();
    };

    
}

#endif
