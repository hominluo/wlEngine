#ifndef TIME_H
#define TIME_H
#include <chrono>
namespace wlEngine {
    class Time {
        public:
            static float deltaTime;
            static double timeAfterGameStart;
            static void update();
        private:
            static std::chrono::time_point<std::chrono::system_clock> oldTime;
    };
}

#endif
