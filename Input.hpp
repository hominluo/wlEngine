#pragma once

#include "System/InputSystem.hpp"
namespace wlEngine {
    /**
     * @brief Input class is used to hide InputSystem from Gameplay Code
     */
    class Input {
    public:
        static uint8_t getKeyStatus(SDL_Scancode); 
        static const std::vector<SDL_Scancode>& getKeypressSequence();
        static bool mousePressingOnScene(int& x, int& y, Button);
        static void getMouseWheel(int& x, int& y);
        static void getJoystick(float& x, float& y);
    };
}
