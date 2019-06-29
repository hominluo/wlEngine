#include "InputSystem.hpp"
#include "UISystem.hpp"

namespace wlEngine {
    SYSTEM_DEFINATION(InputSystem);

    InputSystem::InputSystem() {

        registerSystem(this);
    }   

    void InputSystem::update() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            UISystem::get()->eventUpdate(event);
        }
    }

    Uint8 InputSystem::getKeyStatus(SDL_Scancode& scancode) {
        if(UISystem::get()->isInDeveloperMode()) {
            return SDL_SCANCODE_UNKNOWN; // this means input can't go to gameplay code, Developer control(developer UI) only.
        }
        return SDL_GetKeyboardState(nullptr)[scancode];
    }

}
