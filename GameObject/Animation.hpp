#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL.h>
#include <map>
#include <string>
#include <vector>

namespace wlEngine {
    /* Animation stores information that a gamobject will use to clip the sprint sheet*/

    using Clips = std::vector<SDL_Rect>;
    using ClipsMap = std::map<std::string , Clips>;
    class Animation {
    public:
        Animation();

        void playAnimation(std::string&&);
        void loadClips(const char* path);
        SDL_Rect* getCurrentClip();
        void pause();
    private:
        Clips* currentAnimation;
        int currentFrame;
        float speed;
        double timeStamp;
        ClipsMap clips;

    };
}
#endif
