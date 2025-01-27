#include "AnimationSystem.hpp"
#include "../GameObject/GameObject.hpp"
#include "../Component/Sprite.hpp"
#include "../Component/Animation.hpp"
#include "../Time.hpp"

namespace wlEngine {
    SYSTEM_DEFINATION(AnimationSystem);
    AnimationSystem::AnimationSystem() {
        
    }

    void AnimationSystem::update() {
        for (auto& c : Animation::collection) {
            updateClip(c);           
        }
    }

    void AnimationSystem::updateClip(Animation* a) {
        if(a->animationHasEnded) return;
        a->timeStamp += Time::deltaTime;
        if (a->timeStamp >= a->currentAnimation->frames.at(a->currentFrame).duration) {
            a->timeStamp = 0;
            a->currentFrame++;
            if(a->currentFrame == (int)a->currentAnimation->frames.size() - 1 && !a->recursive) { // AnimationSystem's update is called before RenderSystem (in the same frame, the last frame of the animation is rendered after the animation is set to true)
                a->animationHasEnded = true;
            }
            a->currentFrame %= a->currentAnimation->frames.size();
        }
    }
}
