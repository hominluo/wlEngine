#include "Camera.hpp"
#include "../Graphics/GraphicsManager.hpp"

namespace wlEngine {
    Camera::Camera() : GameObject() {
        bkgWidth = -1;
        bkgHeight = -1;
    };
    Camera::~Camera() {};

    SDL_Rect Camera::getRenderingRect() {
        auto cameraPos = GameObject::transform.getPosition();

        auto graphicsManager = GraphicsManager::getGraphicsManager();
        int winWidth = -1;
        int winHeight = -1;
        graphicsManager->getWindowSize(winWidth, winHeight);

        return SDL_Rect{(int)cameraPos.x, -(int)cameraPos.y, winWidth, winHeight};
    }

    void Camera::setBkgSize(int width, int height) {
        this->bkgWidth = width;
        this->bkgHeight = height;
    }

    void Camera::setPosition(const float& x,const float& y,const float& z) {
        GameObject::setPosition(x,y,z);
    }

}
