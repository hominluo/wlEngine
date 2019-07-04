#ifndef ANIMATION_H
#define ANIMATION_H

#include <map>
#include <string>
#include <vector>

#include "Component.hpp"
#include "Struct/Clip.hpp"

namespace wlEngine {

    using Clips = std::vector<Clip>;
    using ClipsMap = std::map<std::string , Clips>;

    class Animation : public Component{
    public:
        COMPONENT_DECLARATION(Component, Animation, 100);
        Animation(GameObject* go);
        Animation(GameObject* go, const std::string& path);

        void playAnimation(std::string&&);
        void loadClips(const char* path);
        Rect* getCurrentClip();
        void pause();
		bool isPlaying(const std::string&);
    private:
        Clips* currentAnimation;
        int currentFrame = 0;
        float timeStamp = 0;
        int gridX = 0;
        int gridY = 0;
        ClipsMap clips;

        friend class AnimationSystem;
    };
}
#endif
