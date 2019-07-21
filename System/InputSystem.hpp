#pragma once
#include "System.hpp"
#include <SDL_scancode.h>
#include <SDL_mouse.h>
namespace wlEngine {
    class RenderSystem;
    enum class Button {
        Left = SDL_BUTTON_LEFT, Right = SDL_BUTTON_RIGHT
    };
    enum class InputType : uint8_t{
        ButtonUp = 0, ButtonRight = 1, ButtonDown = 2, ButtonLeft = 3, R1 = 4, R2 = 5, L1 = 6, L2 = 7,
    };

    class InputSystem : System {
        SYSTEM_DECLARATION(InputSystem);
    public:
        void setGameplayWindowOffset(const int& x, const int& y);
        bool mousePressingOnScene(int& x, int& y, Button);
        void getMouseWheel(int& x, int& y);
        Uint8 getKeyStatus(SDL_Scancode&);
        const std::vector<SDL_Scancode>& getKeypressSequence();
    private:
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

        float joystickX;
        float joystickY;

        /**
         * @brief record if a button has pressed, this is a once event
         *
         */
        std::vector<bool> buttonPressed;

        /**
         * @brief the sequence of the keypress of this frame
         */
        std::vector<SDL_Scancode> keypressSequence;

        void joyStickUpdate();
        void reset();

        friend class Input;
    };
}
