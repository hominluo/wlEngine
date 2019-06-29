#pragma once

#include "System/InputSystem.hpp"
namespace wlEngine {
    /**
     * @brief Input class is used to hide InputSystem from Gameplay Code
     */
    class Input {
    public:
        static Uint8 getKeyStatus(SDL_Scancode); 
    };
}
