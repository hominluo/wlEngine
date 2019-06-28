#include "UISystem.hpp"
#include "RenderSystem.hpp"
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
    }

    void UISystem::render() {
        ImGui_ImplOpenGL3_NewFrame();   
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        bool showAnotherWindow = true;
        ImGui::Begin("First Window", &showAnotherWindow);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("wlEngine's first UI");
        if (ImGui::Button("Close Me"))
            showAnotherWindow= false;
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void UISystem::init() {
        system = new UISystem();
    }

    void UISystem::update(){
        
    }
}
