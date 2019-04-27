#ifndef ANIMATION_H
#define ANIMATION_H

#include <map>
#include <string>
#include <vector>

#include <SDL.h>

namespace wlEngine {
    /* Animation stores information that a gamobject will use to clip the sprint sheet*/
    struct Clip {
        const float duration;
        SDL_Rect clip;
    };

    using Clips = std::vector<Clip>;
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
        float timeStamp;
        ClipsMap clips;

    };
}
#endif
