#ifndef ANIMATION_H
#define ANIMATION_H

#include <map>
#include <string>
#include <vector>
#include <utility>

#include "Component.hpp"
#include "Struct/Clip.hpp"

namespace wlEngine {
    class Texture;
    struct OneAnimationInfo {
        std::string name;
        Texture* atlas;
        std::vector<Frame> frames;
    };
    using FilePath = std::string;

    class Animation : public Component{
        COMPONENT_DECLARATION(Component, Animation, 100);
        COMPONENT_EDITABLE_DEC();
    public:
        Animation(Entity* go);
		Animation(Entity* go, void** args);

        void playAnimation(const std::string&, bool recursive=true);

        /* Animation loading **************************************/
		void addAnimationFromAseprite(const std::string& name, const FilePath& animationPath, const FilePath& texturePath);
        Rect* getCurrentClip();
        std::string getCurrentClipName();
        void pause();
		bool isPlaying(const std::string&);
        bool hasEnded();
		int getCurrentFrame();
    private:
        OneAnimationInfo* currentAnimation;
        std::map<std::string, OneAnimationInfo> animations; 

        int currentFrame = 0;
        float timeStamp = 0;
		bool recursive; 
        bool animationHasEnded;

        friend class AnimationSystem;
        friend class GameEditor;
    };
}
#endif
