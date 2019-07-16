#pragma once
#include "System.hpp"
#include <SDL_scancode.h>
#include <SDL_mouse.h>
namespace wlEngine {
    class RenderSystem;
    enum class Button {
        Left = SDL_BUTTON_LEFT, Right = SDL_BUTTON_RIGHT
    };
    class InputSystem : System {
        SYSTEM_DECLARATION(InputSystem);
        int mouseX = 0;
        int mouseY = 0;

        int gameplayWindowOffsetX = 0;
        int gameplayWindowOffsetY = 0;

        bool leftMouseClicked = false;
        bool leftMousePressing = false;
        bool rightMouseClicked = false;
        bool rightMousePresssing = false;

        int wheelX = 0;
        int wheelY = 0;
    public:
        void setGameplayWindowOffset(const int& x, const int& y);
        bool mousePressingOnScene(int& x, int& y, Button);
        void getMouseWheel(int& x, int& y);
        Uint8 getKeyStatus(SDL_Scancode&);
    };
}
