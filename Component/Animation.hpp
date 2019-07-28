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

    class Animation : public Component{
        COMPONENT_DECLARATION(Component, Animation, 100);
        COMPONENT_EDITABLE_DEC();
    public:
        Animation(Entity* go, const std::string& path, const int& width, const int& height);
        Animation(Entity* go, const std::string& path, const int& width, const int& height, const std::string& initialAni);
		Animation(Entity* go, void** args);

        void playAnimation(const std::string&, bool recursive=true);
        void loadClips(const char* path);
        Rect* getCurrentClip();
        std::string getCurrentClipName();
        void pause();
		bool isPlaying(const std::string&);
        bool hasEnded();
		int getCurrentFrame();
    private:
        Clips* currentAnimation;
        ClipsMap clips;

        int currentFrame = 0;
        float timeStamp = 0;
        int gridX = 0;
        int gridY = 0;
        int width = 0;
        int height = 0;
		bool recursive; 
        bool animationHasEnded;

        friend class AnimationSystem;
        friend class GameEditor;
    };
}
#endif
