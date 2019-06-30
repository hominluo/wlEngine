#include "UISystem.hpp"
#include "RenderSystem.hpp"
#include "../UI/DeveloperUI.hpp"
#include "../Settings.hpp"
#include <iostream>
namespace wlEngine {
    UISystem* UISystem::get() {return system;}
    UISystem* UISystem::system = nullptr;
    UISystem::UISystem() {
        RenderSystem* renderSystem = RenderSystem::get();
        window = renderSystem->getSDL_Window();
        context = renderSystem->getSDL_GLContext();

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        ImGui::StyleColorsDark();
        ImGui_ImplSDL2_InitForOpenGL(window, context);

        ImGui_ImplOpenGL3_Init("#version 450");
        registerSystem(this);

        if (Settings::settings["development_mode"]) {
            developerUI = new DeveloperUI;
        }
    }

    void UISystem::turnOnDeveloperUI() {

    }

    void UISystem::render() {
        ImGui_ImplOpenGL3_NewFrame();   
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        if (developerUI && developerUISwitch) developerUI->render();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void UISystem::init() {
        system = new UISystem();
    }

    void UISystem::update(){

    }

    void UISystem::eventUpdate(SDL_Event& event) {
        ImGui_ImplSDL2_ProcessEvent(&event);
        switch(event.type) {
            case SDL_KEYDOWN:
                if (event.key.keysym.scancode == SDL_SCANCODE_F5) {
                    developerUISwitch = !developerUISwitch;
                }
                break;
        }        
    }

    UISystem::~UISystem() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }
}
