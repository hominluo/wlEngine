#include <json.hpp>

#include "Animation.hpp"

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

            auto clipsJson = json::parse(jsonStr)["clips"]; // key is the name of the animation
            for (json::iterator iter = clipsJson.begin(); iter != clipsJson.end(); iter++) {
                auto clipsData = iter.value();
                std::vector<std::vector<int>> clipArr = clipsData["clip"];
                std::vector<float> duration = clipsData["duration"];

                for (size_t i = 0 ; i < clipArr.size(); i++) {
                    clips[iter.key()].push_back(Clip{duration[i] , Rect{
                            clipArr[i][0], 
                            clipArr[i][1], 
                            clipArr[i][2], 
                            clipArr[i][3]}});
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

        return &currentAnimation->at(currentFrame).clip;// NEED TO CHANGE
    }
}
