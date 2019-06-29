#pragma once
#include "System.hpp"
#include <SDL_scancode.h>
namespace wlEngine {
    class InputSystem : System {
        SYSTEM_DECLARATION(InputSystem);

    public:
        Uint8 getKeyStatus(SDL_Scancode&);
    };
}
