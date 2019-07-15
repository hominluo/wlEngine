#include "InputSystem.hpp"
#include "RenderSystem.hpp"
#include "../EngineManager.hpp"
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
                            auto currentScene = EngineManager::getwlEngine()->getCurrentScene();
                            currentScene->reloadScene();
                        }
                        else {
                            Settings::engineMode = Settings::EngineMode::Gameplay;
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button == SDL_BUTTON_LEFT) leftMouseClicked = true;
                    else leftMouseClicked = false;
                    if (event.button.button == SDL_BUTTON_RIGHT) rightMouseClicked = true;
                    else rightMouseClicked = false;
                    break;
            }        
            //mouse
        }
    }

    Uint8 InputSystem::getKeyStatus(SDL_Scancode& scancode) {
        return SDL_GetKeyboardState(nullptr)[scancode];
    }

    void InputSystem::setGameplayWindowOffset(const int& x, const int& y) {
        gameplayWindowOffsetX = x;
        gameplayWindowOffsetY = y + 20; // 20 is the title bar
    }

    bool InputSystem::mouseClickedOnScene(int& x, int& y, Button button) {
        auto sceneSize = RenderSystem::get()->getSceneSize();
        bool mouseClicked = button == Button::Left? leftMouseClicked : rightMouseClicked;
        if((SDL_GetMouseState(&mouseX, &mouseY)) && mouseClicked) {
            int sceneHeight = RenderSystem::get()->getSceneSize().y;
            x = mouseX - gameplayWindowOffsetX;
            y = sceneHeight + gameplayWindowOffsetY - mouseY;
            if(x >=0 && y >= 0 && x <= sceneSize.x && y <= sceneSize.y) return true;
            return false;
        }
        return false;
    }
}
