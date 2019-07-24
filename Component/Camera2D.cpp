#include "Camera2D.hpp"
#include "../GameObject/GameObject.hpp"
#include "../System/RenderSystem.hpp"
#include "../Input.hpp"
#include "../Time.hpp"
namespace wlEngine {
    COMPONENT_DEFINATION(Component, Camera2D, 3);
	COMPONENT_EDITABLE_DEF(Camera2D);

    Camera2D::Camera2D(GameObject* go) : Component(go) {
        viewport = RenderSystem::get()->getSceneSize();
        viewportScale = viewport.x / viewport.y;
		transform = go->getComponent<Transform>();
    }

    const CoordTransform& Camera2D::getTransformMatrix() {
//#if SETTINGS_ENGINEMODE 
//        int wheelY;
//        int wheelX;
//        InputSystem::get()->getMouseWheel(wheelX, wheelY);
//        viewport.x += wheelY * viewportScale;
//        viewport.y += wheelY;
//#endif
        coordTransform.view = glm::lookAt(transform->position, transform->position + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
        coordTransform.projection = glm::ortho(0.0f, (float)viewport.x , 0.0f, (float)viewport.y, -1.0f, 1000.0f);
        return coordTransform;
    }

}
