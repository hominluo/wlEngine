#include <json.hpp>

#include "Animation.hpp"
#include "Sprite.hpp"
#include "../GameObject/GameObject.hpp"
#include "../Manager/ResourceManager.hpp"

#include <fstream>
#include <iostream>
namespace wlEngine {
    using Json = nlohmann::json;

    COMPONENT_DEFINATION(Component, Animation, 100);
	COMPONENT_EDITABLE_DEF(Animation);

    Animation::Animation(Entity* go): Component(go), recursive(false), animationHasEnded(true) {
        currentAnimation = nullptr;
        timeStamp = 0;
		currentFrame = 0;
    }

	Animation::Animation(Entity* go, void** args) : Component(go), currentAnimation(nullptr), timeStamp(0), currentFrame(0), recursive(false), animationHasEnded(true) {
        if(args) {
			go->getComponent<Sprite>()->mainTexture->clip(getCurrentClip());
        }
    }

	void Animation::addAnimationFromAseprite(const std::string& name, const FilePath& animationJson, const FilePath& texturePath) {
		std::ifstream jsonInput(animationJson);
        animations[name].atlas = ResourceManager::get()->getTexture(texturePath);
		if (jsonInput.good()) {
			std::string jsonStr(
				(std::istreambuf_iterator<char>(jsonInput)),
				(std::istreambuf_iterator<char>()));
			Json animation = json::parse(jsonStr);
			Json& frames = animation["frames"];
            int sizeOfFrames = frames.size();
			
            for (int i = 0; i < sizeOfFrames; i++) {
                Frame frame;
                frame.duration = frames[i]["duration"].get<float>()/1000; //ms to s
                frame.rect.x = frames[i]["frame"]["x"];
                frame.rect.y = frames[i]["frame"]["y"];
                frame.rect.width = frames[i]["frame"]["w"];
                frame.rect.height = frames[i]["frame"]["h"];
                animations[name].frames.push_back(frame);
            }
		}
	}
    void Animation::playAnimation(const std::string& name, bool recursive) {
        animationHasEnded = false;
		this->recursive = recursive;
        currentAnimation = &animations[name];

        auto sprite = entity->getComponent<Sprite>();
        sprite->mainTexture = currentAnimation->atlas;
        currentFrame = 0;
    }

    void Animation::pause() {
        currentAnimation = nullptr;
    }

    Rect* Animation::getCurrentClip() {
        if (currentAnimation == nullptr) return nullptr;

        return &currentAnimation->frames.at(currentFrame).rect;
    }

    bool Animation::isPlaying(const std::string& name) {
        return currentAnimation == &animations[name];
    }

    std::string Animation::getCurrentClipName() {
        return currentAnimation->name;
    }

    bool Animation::hasEnded() {
        return animationHasEnded;
    }

	int Animation::getCurrentFrame() {
		return currentFrame;
	}

}
