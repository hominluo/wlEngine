#ifndef TIME_H
#define TIME_H
#include <chrono>
namespace wlEngine {
    class Time {
        public:
            static double deltaTime;
            static void update();
        private:
            static std::chrono::time_point<std::chrono::high_resolution_clock> oldTime;
    };
}

#endif
