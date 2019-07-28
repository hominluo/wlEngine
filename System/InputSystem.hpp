#pragma once
#include "System.hpp"
#include <SDL_scancode.h>
#include <SDL_mouse.h>
#include <SDL_joystick.h>
#include <SDL_events.h>
namespace wlEngine {
    class RenderSystem;

    enum class InputType : uint8_t{
        ButtonUp = 0, ButtonRight = 1, ButtonDown = 2, ButtonLeft = 3, R1 = 4, R2 = 5, L1 = 6, L2 = 7,
    };

    struct GameControllerInput{
        Sint16 leftAxisX = 0;
        Sint16 leftAxisY = 0;
        Sint16 rightAxisX = 0;
        Sint16 rightAxisY = 0;
        Uint8 buttonLeft = 0;
        Uint8 buttonUp = 0;
        Uint8 buttonRight = 0;
        Uint8 buttonDown = 0;
    };

    class InputSystem : System {
        SYSTEM_DECLARATION(InputSystem);
    public:
        void getMouseWheel(int& x, int& y);
        Uint8 getKeyStatus(SDL_Scancode&);
        const std::vector<SDL_Scancode>& getKeypressSequence();
    private:
        int mouseX = 0;
        int mouseY = 0;

        bool leftMouseClicked = false;
        bool leftMousePressing = false;
        bool rightMouseClicked = false;
        bool rightMousePresssing = false;

        int wheelX = 0;
        int wheelY = 0;

        GameControllerInput gameControllerInput;
        /**
         * @brief record if a button has pressed, this is a once event
         *
         */
        std::vector<bool> buttonPressed;

        /**
         * @brief the sequence of the keypress of this frame
         */
        std::vector<SDL_Scancode> keypressSequence;

        void reset();
        void keyDown(const SDL_Event&);
        void controllerAxisEvent(const SDL_ControllerAxisEvent& axisEvent);
		SDL_GameController* gameController;
		const int GAMECONTROLLER_AXIS_DEADZONE = 8000;

        friend class Input;
    };
}
