#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.hpp"

namespace wlEngine {
    class Camera : public GameObject {
        public:
            Camera();
            ~Camera();

            glm::vec3 getPosition();
    };
}

#endif
