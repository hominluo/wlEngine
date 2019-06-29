#include "Camera.hpp"
#include "../Time.hpp"
#include "../Component/Transform.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace wlEngine {
    class Camera2D : public wlEngine::Camera {
    public:
        Camera2D();
        glm::mat4 getViewMatrix() override ;

        void update() override;

    private:
        float speed = 100.0;
        Transform* transform;
    };
}
