#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <glm/vec3.hpp>

namespace wlEngine {
    //TO_DO: There should be a actual position and rendering position
    //user sets the actual position, Transform calculates the rendering
    //position for Z
    class Transform {
        //no rotaion and flip yet
    public:
        Transform(float x, float y, float z);
        Transform();
        
        glm::vec3 getPosition(); // TO_DO:this function should do some calculation about 2.5 D when z has some value

        void setPosition(const float& x, const float& y, const float& z);
        void moveBy(const float& x, const float& y, const float& z);
    private:

        glm::vec3 position;

    friend class GameObject;
    };
}

#endif
