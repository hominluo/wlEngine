#include "Input.hpp"
#include <iostream>
namespace wlEngine {
	
    uint8_t Input::getKeyStatus(SDL_Scancode scancode) {
        return InputSystem::get()->getKeyStatus(scancode);
    }

    const std::vector<SDL_Scancode>& Input::getKeypressSequence() {
        return InputSystem::get()->getKeypressSequence();
    }

    bool Input::mousePressingOnScene(int& x, int& y, Button button) {
        return InputSystem::get()->mousePressingOnScene(x,y, button);
    }

    void Input::getMouseWheel(int& x, int& y) {
        return InputSystem::get()->getMouseWheel(x,y);
    }

    ControllerAxisType Input::getControllerAxis(const ControllerAxis& axis) {
		return SDL_GameControllerGetAxis(InputSystem::get()->gameController, static_cast<SDL_GameControllerAxis>(axis));
    }

	ControllerButtonType Input::getControllerButton(const ControllerButton& button) {
		return SDL_GameControllerGetButton(InputSystem::get()->gameController, static_cast<SDL_GameControllerButton>(button));
	}
}
