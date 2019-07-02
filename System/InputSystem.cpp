#include "InputSystem.hpp"
#include "RenderSystem.hpp"
#include "../Settings.hpp"
namespace wlEngine {
    SYSTEM_DEFINATION(InputSystem);

    InputSystem::InputSystem() {
        registerSystem(this);
    }   

    void InputSystem::update() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            RenderSystem::get()->inputHandler(event);
            switch(event.type) {
                case SDL_KEYDOWN:
                    if (event.key.keysym.scancode == SDL_SCANCODE_F5) {
                        if(Settings::engineMode == Settings::EngineMode::Editor) {
                            Settings::engineMode = Settings::EngineMode::Gameplay;
                        }
                        else {
                            Settings::engineMode = Settings::EngineMode::Editor;
                        }
                    }
                    break;
            }        
        }
    }

    Uint8 InputSystem::getKeyStatus(SDL_Scancode& scancode) {
        if(Settings::engineMode == Settings::EngineMode::Editor) {
            return SDL_SCANCODE_UNKNOWN; // this means input can't go to gameplay code, Developer control(developer UI) only.
        }
        return SDL_GetKeyboardState(nullptr)[scancode];
    }

}
