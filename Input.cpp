#include "Input.hpp"

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

    void Input::getJoystick(float& x, float& y) {
        x = InputSystem::get()->joystickX;
        y = InputSystem::get()->joystickY;
    }
}
