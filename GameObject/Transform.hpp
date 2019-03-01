#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Math.hpp"
namespace wlEngine {

    class Transform {
    public:
        Transform(float x, float y, float z);

        Vector3<float> getPosition(); // this function should do some calculation about 2.5 D when z has some value
    private:
        Vector3<float> position;
        
    };
}

#endif
