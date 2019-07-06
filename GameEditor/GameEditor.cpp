#include <fstream>
#include <sstream>
#include "../imgui/imgui.h"

#include "GameEditor.hpp"
#include "../EngineManager.hpp"
#include "../Manager/ResourceManager.hpp"

#include "../Component/Transform.hpp"
#include "../Component/Animation.hpp"
#include "../Component/Sprite.hpp"

#include "../System/RenderSystem.hpp"
#include "../Settings.hpp"
namespace wlEngine {
    GameEditor::GameEditor() : selectedGameObject(nullptr) {

    }

    GameEditor::~GameEditor(){

    }

    void GameEditor::render(void** data) {
        showGameWindow(data);
        showMenu();
        showAllGameObjects();
        showResourceWindow();
    }

    void GameEditor::showGameWindow(void** data) {
        auto& style = ImGui::GetStyle();
        auto windowPadding = style.WindowPadding;
        style.WindowPadding = {0,0};
        std::string windowName;
        if (Settings::engineMode == Settings::EngineMode::Gameplay) windowName = "Game: GamePlay###";
        else windowName = "Game: Editor###";
        ImGui::Begin(windowName.data(),nullptr, ImGuiWindowFlags_NoResize);
        float sceneWidth = *(int*)(data[1]);
        float sceneHeight = *(int*)(data[2]);
        ImGui::Image((void*)*(unsigned int*)(data[0]), {sceneWidth,sceneHeight}, {0,1}, {1,0});//one commnet from imgui.cpp: my_void_ptr = (void*)(intptr_t)my_tex;                  // cast a GLuint into a void* (we don't take its address! we literally store the value inside the pointer)
        ImGui::End();
        style.WindowPadding = windowPadding;
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

            for (auto& c : go->components) {
                if (c->getId() == Transform::componentId) {
                    bool open = ImGui::TreeNodeEx("Transform");
                    if(open){
                        showTransformInfo(go);   
                        ImGui::TreePop();
                    }
                }
                else if (c->getId() == Sprite::componentId) {
                    bool open = ImGui::TreeNodeEx("Sprite");
                    if (open) {
                        showSpriteInfo(static_cast<Sprite*>(c.get()));
                        ImGui::TreePop();
                    }
                }
                else if (c->getId() == Animation::componentId) {
                    bool open = ImGui::TreeNodeEx("Animation");
                    if (open){
                        showAnimationInfo(static_cast<Animation*>(c.get()));
                        ImGui::TreePop();
                    }
                }
            }
        }
        ImGui::End();

    }

    void GameEditor::showMenu() {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                ImGui::MenuItem("Save", "CTRL+S");
                if(ImGui::IsItemClicked()) {
                    const nlohmann::json& scene_jsonRef = EngineManager::getwlEngine()->getCurrentScene()->scene_json;
                    std::ofstream ofs;
                    ofs.open(scene_jsonRef["scene_path"].get<std::string>());
                    if (ofs.good()) {
                        ofs << scene_jsonRef.dump();
                    }
                    ofs.close();
                }
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

    void GameEditor::showAnimationInfo(Animation* animation){
        std::string current_item = animation->getCurrentClipName();
        if (ImGui::BeginCombo("animation", current_item.data())) {
            for (auto iter : animation->clips) {
                bool isSelected = (current_item == iter.first); // You can store your selection however you want, outside or inside your objects
                if(ImGui::Selectable(iter.first.data(), &isSelected)){
                    animation->playAnimation(iter.first);
                    ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
                }
            }
            ImGui::EndCombo();
        }
        Rect* clip = animation->getCurrentClip();
        ImGui::Text("offset X: %d", clip->x);
        ImGui::Text("offset Y: %d", clip->y);
        ImGui::Text("width: %d", clip->width);
        ImGui::Text("height: %d", clip->height);
    }

    void GameEditor::showTransformInfo(GameObject* go) {
        auto transform = go->getComponent<Transform>();
        auto pos = transform->getLocalPosition();

        ImGui::InputFloat("local x", &pos.x);
        ImGui::InputFloat("local y", &pos.y);
        ImGui::InputFloat("local z", &pos.z);

        float scale_f = transform->scale.x;
        ImGui::InputFloat("Scale Aspect Ratio", &scale_f);

        transform->setScale(scale_f, scale_f, scale_f);
        transform->setLocalPosition(pos);

        (*go->json_ptr)["components"]["Transform"][0] = pos.x;
        (*go->json_ptr)["components"]["Transform"][1] = pos.y;
        (*go->json_ptr)["components"]["Transform"][2] = pos.z;
    }

    void GameEditor::showResourceWindow() {
        auto textures = ResourceManager::get()->getTextures();
        ImGui::Begin("Resource");
        for (auto texture : textures) {
            ImGui::Image((void*)texture.second.mTexture, {(float)texture.second.mWidth, (float)texture.second.mHeight}, {0,1}, {1,0});
        }
        ImGui::End();
    }

    void GameEditor::showSpriteInfo(Sprite* sprite) {
        ImGui::Image((void*)sprite->texture->mTexture, {(float)sprite->texture->mWidth, (float)sprite->texture->mHeight}, {0,1}, {1,0});
    }
}
