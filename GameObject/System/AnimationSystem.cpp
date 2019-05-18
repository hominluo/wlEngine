#include "AnimationSystem.hpp"
#include "../GameObject.hpp"
#include "../Component/Texture.hpp"
#include "../Component/Animation.hpp"
#include "../../Time.hpp"
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
        a->timeStamp += Time::deltaTime;
        if (a->timeStamp >= a->currentAnimation->at(a->currentFrame).duration) { // 1 is the duration of this frame
            a->timeStamp = 0;
            a->currentFrame++;
            a->currentFrame %= a->currentAnimation->size();
        }

        auto texture = a->gameObject->getComponent<Texture>();
        texture->clip(a->getCurrentClip());
    }
}
