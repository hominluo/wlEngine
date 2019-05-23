#include "Time.hpp"
#include <iostream>
namespace wlEngine {
    float Time::deltaTime = 0;
    double Time::timeAfterGameStart = 0;
    std::chrono::time_point<std::chrono::system_clock> Time::oldTime = std::chrono::system_clock::now();
    void Time::update() {
        auto newTime = std::chrono::system_clock::now();
        deltaTime = std::chrono::duration<float>(newTime - oldTime).count();
        timeAfterGameStart += deltaTime;
        oldTime = newTime;
    }
}
