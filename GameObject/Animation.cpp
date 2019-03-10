#include "Animation.hpp"
#include "../third_party/json.hpp"
#include "../Time.hpp"

#include <fstream>
#include <iostream>
namespace wlEngine {
    using json = nlohmann::json;
    Animation::Animation() {
        currentAnimation = nullptr;
    }

    void Animation::loadClips(const char* path) {
        std::ifstream jsonInput(path);

        if (jsonInput.good()) {
            std::string jsonStr (
                    (std::istreambuf_iterator<char>(jsonInput)), 
                    (std::istreambuf_iterator<char>()        ));

            auto clipsJson = json::parse(jsonStr)["clips"]; // key is the name of the animation
            for (json::iterator iter = clipsJson.begin(); iter != clipsJson.end(); iter++) {
                std::vector<std::vector<int>> clipsData = iter.value();
                for (auto dataIter = clipsData.begin(); dataIter != clipsData.end(); dataIter++) {
                    clips[iter.key()].push_back(SDL_Rect{dataIter->at(0), dataIter->at(1), dataIter->at(2), dataIter->at(3)});
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

        currentFrame++;
        currentFrame %= currentAnimation->size();
        return &currentAnimation->at(currentFrame);// NEED TO CHANGE
    }
}
