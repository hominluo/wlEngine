#include "Animation.hpp"
#include "../third_party/json.hpp"
#include "../Time.hpp"

#include <fstream>
#include <iostream>
namespace wlEngine {
    using json = nlohmann::json;
    Animation::Animation() {
        currentAnimation = nullptr;
        timeStamp = 0;
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
                    clips[iter.key()].push_back(Clip{duration[i] , SDL_Rect{
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

    SDL_Rect* Animation::getCurrentClip() {
        if (currentAnimation == nullptr) return nullptr;
        
        timeStamp += Time::deltaTime;
        if (timeStamp >= currentAnimation->at(currentFrame).duration) { // 1 is the duration of this frame
            timeStamp = 0;
            currentFrame++;
            currentFrame %= currentAnimation->size();
        }
        return &currentAnimation->at(currentFrame).clip;// NEED TO CHANGE
    }
}
