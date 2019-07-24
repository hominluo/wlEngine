#pragma once

#include "System/InputSystem.hpp"
namespace wlEngine {
    using ControllerAxisType=Sint16;
	using ControllerButtonType=Uint8;
	enum class ControllerButton {
		ButtonLeft = SDL_CONTROLLER_BUTTON_X,
		ButtonRight = SDL_CONTROLLER_BUTTON_B,
		ButtonUp = SDL_CONTROLLER_BUTTON_Y,
		ButtonDown = SDL_CONTROLLER_BUTTON_A,
        LeftStick = SDL_CONTROLLER_BUTTON_LEFTSHOULDER
	};

	enum class ControllerAxis {
		AxisLeftX = SDL_CONTROLLER_AXIS_LEFTX,
		AxisLeftY = SDL_CONTROLLER_AXIS_LEFTY,
		AxisRightX = SDL_CONTROLLER_AXIS_RIGHTX,
		AxisRightY = SDL_CONTROLLER_AXIS_RIGHTY,
		TriggerLeft = SDL_CONTROLLER_AXIS_TRIGGERLEFT,
		TriggerRight = SDL_CONTROLLER_AXIS_TRIGGERRIGHT,
	};
    /**
     * @brief Input class is used to hide InputSystem from Gameplay Code
     */
    class Input {
    public:
        static const ControllerAxisType AXIS_MAX = 0x7fff;
        static uint8_t getKeyStatus(SDL_Scancode); 
        static const std::vector<SDL_Scancode>& getKeypressSequence();
        static bool mousePressingOnScene(int& x, int& y, Button);
        static void getMouseWheel(int& x, int& y);
        static ControllerAxisType getControllerAxis(const ControllerAxis& axis);
		static ControllerButtonType getControllerButton(const ControllerButton& button);
    };
}
