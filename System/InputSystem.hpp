#pragma once
#include "System.hpp"
#include <SDL_scancode.h>
namespace wlEngine {
    class RenderSystem;
    class InputSystem : System {
        SYSTEM_DECLARATION(InputSystem);
        int mouseX = 0;
        int mouseY = 0;

        int gameplayWindowOffsetX = 0;
        int gameplayWindowOffsetY = 0;

    public:
        void setGameplayWindowOffset(const int& x, const int& y);
        Uint8 getKeyStatus(SDL_Scancode&);
        bool mousePressingOnScene(int& x, int& y);
    };
}
