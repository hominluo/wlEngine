#pragma once

namespace wlEngine {
    struct Rect {
        int x;
        int y;
        int width;
        int height;  
        Rect(const int& x, const int& y, const int& width, const int& height): x(x), y(y), width(width), height(height){};
    };
    /* Animation stores information that a gamobject will use to clip the sprint sheet*/
    struct Clip {
        const float duration;
        Rect clip;
    };
}
