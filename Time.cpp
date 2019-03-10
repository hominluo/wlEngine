#include "Time.hpp"
namespace wlEngine {
    double Time::deltaTime = 0;
    std::chrono::time_point<std::chrono::high_resolution_clock> Time::oldTime = std::chrono::high_resolution_clock::now();
    void Time::update() {
        auto newTime = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration<double>(newTime - oldTime).count();
        oldTime = newTime;
    }
}
