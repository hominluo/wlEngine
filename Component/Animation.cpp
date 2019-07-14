#include <json.hpp>

#include "Animation.hpp"
#include "Sprite.hpp"
#include "../GameObject/GameObject.hpp"

#include <fstream>
#include <iostream>
namespace wlEngine {
    using json = nlohmann::json;

    COMPONENT_DEFINATION(Component, Animation, 100);
	COMPONENT_EDITABLE_DEF(Animation);

    Animation::Animation(GameObject* go, const std::string& path, const int& width, const int& height): Component(go) {
        currentAnimation = nullptr;
        timeStamp = 0;
		currentFrame = 0;
        this->width = width;
        this->height = height;
		loadClips(path.data());
    }

	Animation::Animation(GameObject* go, void** args) : Component(go) {
		std::string* path = static_cast<std::string*>(args[0]);
		this->width = *static_cast<float*>(args[1]);
		this->height = *static_cast<float*>(args[2]);
		auto initialAni = *static_cast<std::string*>(args[3]);

		currentAnimation = nullptr;
		timeStamp = 0;
		currentFrame = 0;
		loadClips(path->data());
		playAnimation(initialAni);
	}

    Animation::Animation(GameObject* go, const std::string& path, const int& width, const int& height, const std::string& initialAni) : Animation(go, path,width, height){
		playAnimation(initialAni);
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

            int clipWidth = width / gridX;
            int clipHeight = height / gridY;

            for (json::iterator iter = clipsJson.begin(); iter != clipsJson.end(); ++iter) {
                auto clipsData = iter.value();

                std::vector<std::vector<int>> clipArr = clipsData["clip"];
                std::vector<float> duration = clipsData["duration"];


                for (size_t i = 0 ; i < clipArr.size(); i++) {
                    clips[iter.key()].first = iter.key();
                    clips[iter.key()].second.push_back(Clip{duration[i] , Rect{
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
        jsonInput.close();

    }
    void Animation::playAnimation(const std::string& name) {
        currentAnimation = &clips[name];
        currentFrame = 0;
    }

    void Animation::pause() {
        currentAnimation = nullptr;
    }

    Rect* Animation::getCurrentClip() {
        if (currentAnimation == nullptr) return nullptr;

        return &currentAnimation->second.at(currentFrame).clip;
    }

    bool Animation::isPlaying(const std::string& name) {
        return currentAnimation == &clips[name];
    }

    std::string Animation::getCurrentClipName() {
        return currentAnimation->first;
    }
}
