#include "InputSystem.hpp"
#include "RenderSystem.hpp"
#include "../EngineManager.hpp"
#include "../Settings.hpp"
namespace wlEngine {
    SYSTEM_DEFINATION(InputSystem);

    InputSystem::InputSystem() : buttonPressed(8), joystickX(0), joystickY(0) {
        registerSystem(this);
    }   

    void InputSystem::update() {
        SDL_Event event;
        reset();
        joyStickUpdate();
        while (SDL_PollEvent(&event)) {
            if (Settings::engineMode == Settings::EngineMode::Editor) RenderSystem::get()->inputHandler(event);			
            switch(event.type) {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_J:
                            buttonPressed[static_cast<uint8_t>(InputType::ButtonLeft)] = true;
                            break;
                        case SDL_SCANCODE_K:
                            buttonPressed[static_cast<uint8_t>(InputType::ButtonDown)] = true;
                            break;
                        case SDL_SCANCODE_F5:
                            if (Settings::engineMode == Settings::EngineMode::Gameplay){
                                Settings::engineMode = Settings::EngineMode::Editor;
                                auto currentScene = EngineManager::getwlEngine()->getCurrentScene();
                                currentScene->reloadScene();
                            }
                            else {
                                Settings::engineMode = Settings::EngineMode::Gameplay;
                            }
                            break;
                        default:
                            break;
                    }
                    keypressSequence.push_back(event.key.keysym.scancode);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button == SDL_BUTTON_LEFT) leftMouseClicked = true;
                    if (event.button.button == SDL_BUTTON_RIGHT) rightMouseClicked = true;
                    break;
                case SDL_MOUSEWHEEL:
                    wheelX = event.wheel.x;
                    wheelY = event.wheel.y;                   
                    break;
            }        
        }
    }

    Uint8 InputSystem::getKeyStatus(SDL_Scancode& scancode) {
        return SDL_GetKeyboardState(nullptr)[scancode];
    }

    void InputSystem::setGameplayWindowOffset(const int& x, const int& y) {
        gameplayWindowOffsetX = x;
        gameplayWindowOffsetY = y + 20; // 20 is the title bar
    }

    bool InputSystem::mousePressingOnScene(int& x, int& y, Button button) {
        auto sceneSize = RenderSystem::get()->getSceneSize();
        uint8_t mask = button == Button::Left ? SDL_BUTTON_LEFT : SDL_BUTTON_RIGHT;

        if((SDL_GetMouseState(&mouseX, &mouseY)) & SDL_BUTTON(mask)) {
            int sceneHeight = RenderSystem::get()->getSceneSize().y;
            x = mouseX - gameplayWindowOffsetX;
            y = sceneHeight + gameplayWindowOffsetY - mouseY;
            if(x >=0 && y >= 0 && x <= sceneSize.x && y <= sceneSize.y) return true;
            return false;
        }
        int sceneHeight = RenderSystem::get()->getSceneSize().y;
        x = mouseX - gameplayWindowOffsetX;
        y = sceneHeight + gameplayWindowOffsetY - mouseY;
        return false;
    }

    void InputSystem::getMouseWheel(int& x, int& y) {
        x = wheelX;
        y = wheelY;
    }

    void InputSystem::reset() {
        wheelY = 0;
        leftMouseClicked = false;
        rightMouseClicked = false;

        keypressSequence.clear();
        std::fill(buttonPressed.begin(), buttonPressed.end(), false);
    }

    const std::vector<SDL_Scancode>& InputSystem::getKeypressSequence() {
        return keypressSequence;
    }

    void InputSystem::joyStickUpdate() {
        auto keyboardState = SDL_GetKeyboardState(nullptr);
        joystickX = 0;
        joystickY = 0;
        if (keyboardState[SDL_SCANCODE_W]) joystickY = 1;
        if (keyboardState[SDL_SCANCODE_S]) joystickY = -1;
        if (keyboardState[SDL_SCANCODE_W] && keyboardState[SDL_SCANCODE_S]) joystickY = 0;
        if (keyboardState[SDL_SCANCODE_D]) joystickX = 1;
        if (keyboardState[SDL_SCANCODE_A]) joystickX = -1;
        if (keyboardState[SDL_SCANCODE_D] && keyboardState[SDL_SCANCODE_A]) joystickX = 0;
    }
}
