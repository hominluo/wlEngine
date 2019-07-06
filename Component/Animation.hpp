#ifndef ANIMATION_H
#define ANIMATION_H

#include <map>
#include <string>
#include <vector>
#include <utility>

#include "Component.hpp"
#include "Struct/Clip.hpp"

namespace wlEngine {

    using Clips = std::pair<std::string, std::vector<Clip>>;
    using ClipsMap = std::map<std::string , Clips>;

    class Sprite;
    class Animation : public Component{
    public:
        COMPONENT_DECLARATION(Component, Animation, 100);
        COMPONENT_EDITABLE_DEC();
        Animation(GameObject* go);
        Animation(GameObject* go, const std::string& path);
        Animation(GameObject* go, const std::string& path, const std::string& initialAni);

        void playAnimation(const std::string&);
        void loadClips(const char* path);
        Rect* getCurrentClip();
        std::string getCurrentClipName();
        void pause();
		bool isPlaying(const std::string&);
    private:
        Sprite* sprite = nullptr;
        Clips* currentAnimation;
        ClipsMap clips;

        int currentFrame = 0;
        float timeStamp = 0;
        int gridX = 0;
        int gridY = 0;

        friend class AnimationSystem;
        friend class GameEditor;
    };
}
#endif
