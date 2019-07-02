#include <fstream>
#include <sstream>
#include "../imgui/imgui.h"

#include "GameEditor.hpp"
#include "../EngineManager.hpp"

#include "../Component/Transform.hpp"
#include "../System/RenderSystem.hpp"
namespace wlEngine {
    GameEditor::GameEditor() : selectedGameObject(nullptr) {

    }

    GameEditor::~GameEditor(){

    }

    void GameEditor::render() {
        showMenu();
        showAllGameObjects();
    }

    void GameEditor::showAllGameObjects() {
        ImGui::Begin("Scene Graph", nullptr, ImGuiWindowFlags_None);
        auto gameObjects = EngineManager::getwlEngine()->getCurrentScene()->getSceneGraph();
        pushGameObject(gameObjects->begin(), gameObjects);
        ImGui::End();
        showGameObjectInfo();
    }

    void GameEditor::pushGameObject(std::set<GameObject*>::iterator iter, const std::set<GameObject*>* gameObjects) {
        if(iter != gameObjects->end()) {
            bool open = ImGui::TreeNodeEx((*iter)->name.c_str(), ImGuiTreeNodeFlags_OpenOnArrow);

            if(ImGui::IsItemClicked() && (ImGui::GetMousePos().x - ImGui::GetItemRectMin().x) > ImGui::GetTreeNodeToLabelSpacing()) {
                selectedGameObject = *iter;
            }

            if(open) {
                pushGameObject((*iter)->children.begin(), &(*iter)->children);
                ImGui::TreePop();
            }
            pushGameObject(++iter, gameObjects);

        }
    }

    void GameEditor::showGameObjectInfo() {
        ImGui::Begin("GameObject");
        if(selectedGameObject) {
            GameObject* go = selectedGameObject;
            ImGui::Text("%s", go->name.c_str());
            auto transform = go->getComponent<Transform>();
            auto pos = transform->getLocalPosition();

            char x[40];
            char y[40];
            char z[40];
            strcpy(x, std::to_string((int)pos.x).c_str());
            strcpy(y, std::to_string((int)pos.y).c_str());
            strcpy(z, std::to_string((int)pos.z).c_str());
            ImGui::InputText("local x", x, IM_ARRAYSIZE(x));
            ImGui::InputText("local y", y, IM_ARRAYSIZE(y));
            ImGui::InputText("local z", z, IM_ARRAYSIZE(z));

            float scale_f = transform->scale.x;
            ImGui::InputFloat("Scale Aspect Ratio", &scale_f);
            
            transform->setScale(scale_f, scale_f, scale_f);
            transform->setLocalPosition({atoi(x), atoi(y), atoi(z)});
        }
        ImGui::End();

    }

    void GameEditor::showMenu() {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
                if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
                ImGui::Separator();
                if (ImGui::MenuItem("Cut", "CTRL+X")) {}
                if (ImGui::MenuItem("Copy", "CTRL+C")) {}
                if (ImGui::MenuItem("Paste", "CTRL+V")) {}
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

    void GameEditor::loadScene(const std::string& filePath) {
        
    }
}
