#include "InputSystem.hpp"
#include "RenderSystem.hpp"
#include "../EngineManager.hpp"
#include "../Settings.hpp"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_sdl.h"
namespace wlEngine {
    SYSTEM_DEFINATION(InputSystem);

    InputSystem::InputSystem() : buttonPressed(8), gameController(nullptr){
		SDL_GameControllerEventState(SDL_ENABLE);
		if (SDL_NumJoysticks() > 0) {
			gameController = SDL_GameControllerOpen(0);
		}
        registerSystem(this);
    }   

    void InputSystem::update() {
        SDL_Event event;
        reset();
        while (SDL_PollEvent(&event)) {
            if (Settings::engineMode == Settings::EngineMode::Editor) ImGui_ImplSDL2_ProcessEvent(&event);
            switch(event.type) {
                case SDL_KEYDOWN:
                    keyDown(event);
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

    void InputSystem::keyDown(const SDL_Event& event) {
        switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_J:
                buttonPressed[static_cast<uint8_t>(InputType::ButtonLeft)] = true;
                break;
            case SDL_SCANCODE_K:
                buttonPressed[static_cast<uint8_t>(InputType::ButtonDown)] = true;
                break;
#if SETTINGS_ENGINEMODE
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
#endif
            default:
                break;
        }
        keypressSequence.push_back(event.key.keysym.scancode);
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

    void InputSystem::controllerAxisEvent(const SDL_ControllerAxisEvent& axisEvent) {
        if (axisEvent.which == 0) { //only support one controller right now
			Sint16 axisValue = axisEvent.value;
			if (-GAMECONTROLLER_AXIS_DEADZONE < axisValue && axisValue < GAMECONTROLLER_AXIS_DEADZONE)
				axisValue = 0;
			switch (axisEvent.axis)
			{
			case SDL_CONTROLLER_AXIS_LEFTX:
                gameControllerInput.leftAxisX = axisValue;
				break;
			case SDL_CONTROLLER_AXIS_LEFTY:
                gameControllerInput.leftAxisY = -axisValue; // y axis is flipped
				break;
			case SDL_CONTROLLER_AXIS_RIGHTX:
                gameControllerInput.rightAxisX = axisValue;
				break;
			case SDL_CONTROLLER_AXIS_RIGHTY:
                gameControllerInput.rightAxisY = -axisValue;  // y axis is flipped
				break;
            case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
                std::cout << axisValue << std::endl;
			default:
				break;
			}
            
        }
    }
}
