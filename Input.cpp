#include "Input.hpp"

namespace wlEngine {
    Uint8 Input::getKeyStatus(SDL_Scancode scancode) {
        return InputSystem::get()->getKeyStatus(scancode);
    }
}
