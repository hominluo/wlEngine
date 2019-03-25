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
        glm::vec3 getLocalPosition();

        void setLocalPosition(const float& x, const float& y, const float& z);

        void setPosition(const float& x, const float& y, const float& z);
        void moveBy(const float& x, const float& y, const float& z);
    private:

        void moveToParent(Transform*);
        glm::vec3 position;
        glm::vec3 localPosition;

    friend class GameObject;
    };
}

#endif
