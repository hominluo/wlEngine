#include <json.hpp>

#include "Animation.hpp"
#include "Sprite.hpp"
#include "../GameObject/GameObject.hpp"

#include <fstream>
#include <iostream>
namespace wlEngine {
    using json = nlohmann::json;

    COMPONENT_DEFINATION(Component, Animation, 100);

    Animation::Animation(GameObject* go): Component(go) {
        currentAnimation = nullptr;
        timeStamp = 0;
		currentFrame = 0;
    }

    Animation::Animation(GameObject* go, const std::string& path) : Component(go) {
        currentAnimation = nullptr;
        timeStamp = 0;
        currentFrame = 0;
        loadClips(path.data());
    }

    void Animation::loadClips(const char* path) {
        std::ifstream jsonInput(path);

        if (jsonInput.good()) {
            std::string jsonStr (
                    (std::istreambuf_iterator<char>(jsonInput)), 
                    (std::istreambuf_iterator<char>()        ));
			auto animation = json::parse(jsonStr);
			auto clipsJson = animation["clips"]; // key is the name of the animation
			std::vector<int> grid = animation["grid"];

			gridX = grid[0];
			gridY = grid[1];

            auto sprite = gameObject->getComponent<Sprite>();
            int clipWidth = sprite->getWidth() / gridX;
            int clipHeight = sprite->getHeight() / gridY;

            for (json::iterator iter = clipsJson.begin(); iter != clipsJson.end(); ++iter) {
                auto clipsData = iter.value();
               
                std::vector<std::vector<int>> clipArr = clipsData["clip"];
                std::vector<float> duration = clipsData["duration"];


                for (size_t i = 0 ; i < clipArr.size(); i++) {
                    clips[iter.key()].push_back(Clip{duration[i] , Rect{
                            clipArr[i][0] * clipWidth, 
                            clipArr[i][1] * clipHeight, 
                            clipWidth, 
                            clipHeight}});
                }
            }
        }
        else {
            std::cerr << "wlEngine::Animation: fail to load json at " << path; 
        }

    }
    void Animation::playAnimation(std::string&& name) {
        currentAnimation = &clips[name];
        currentFrame = 0;
    }

    void Animation::pause() {
        currentAnimation = nullptr;
    }

    Rect* Animation::getCurrentClip() {
        if (currentAnimation == nullptr) return nullptr;

        return &currentAnimation->at(currentFrame).clip;
    }

	bool Animation::isPlaying(const std::string& name) {
		return currentAnimation == &clips[name];
	}
}
