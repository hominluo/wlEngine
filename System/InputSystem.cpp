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
            if (Settings::engineMode == Settings::EngineMode::Editor)
                RenderSystem::get()->inputHandler(event);
            switch(event.type) {
                case SDL_KEYDOWN:
                    if (event.key.keysym.scancode == SDL_SCANCODE_F5) {
                        if (Settings::engineMode == Settings::EngineMode::Gameplay){
                            Settings::engineMode = Settings::EngineMode::Editor;
                        }
                        else {
                            Settings::engineMode = Settings::EngineMode::Gameplay;
                        }
                    }
                    break;
            }        
        }
    }

    Uint8 InputSystem::getKeyStatus(SDL_Scancode& scancode) {
        return SDL_GetKeyboardState(nullptr)[scancode];
    }

}
