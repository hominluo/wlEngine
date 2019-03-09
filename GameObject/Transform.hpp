#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../Math/Vector3.hpp"

namespace wlEngine {

    class Transform {
    public:
        Transform(float x, float y, float z);
        
        Vector3<float> getPosition(); // this function should do some calculation about 2.5 D when z has some value
        Vector3<float> getLocalPosition();

        void setLocalPosition(const float& x, const float& y, const float& z);

        void setPosition(const float& x, const float& y, const float& z);
        void moveBy(const float& x, const float& y, const float& z);
    private:

        void moveToParent(Transform*);
        Vector3<float> position;
        Vector3<float> localPosition;

    friend class GameObject;
    };
}

#endif
