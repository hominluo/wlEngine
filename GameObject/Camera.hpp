#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.hpp"

namespace wlEngine {
    class Camera : public GameObject {
        public:
            Camera();
            ~Camera();

            // TO_DO: this function should provides more information about x, y
            // position of the rendering, it's currently just 0,0
            // which leads to the stretching effect
            SDL_Rect getRenderingRect();

            void setBkgSize(int width, int height);

            //prevent camera goes out of the bound of static background of the scene
            void setPosition(const float& x,const float& y,const float& z);
            void moveBy(const float& x, const float& y, const float& z);
        
        protected:
            int bkgWidth;
            int bkgHeight;

    };
}

#endif
