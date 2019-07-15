#include <fstream>
#include <sstream>
#include <dirent.h>
#include "../imgui/imgui.h"

#include "GameEditor.hpp"
#include "../EngineManager.hpp"
#include "../Manager/ResourceManager.hpp"

#include "../Component/Transform.hpp"
#include "../Component/Animation.hpp"
#include "../Component/Sprite.hpp"

#include "../System/RenderSystem.hpp"
#include "../System/InputSystem.hpp"
#include "../Settings.hpp"

#include "../Utility/Utility.hpp"
namespace wlEngine {
    GameEditor::GameEditor() : selectedGameObject(nullptr) {
    }

    GameEditor::~GameEditor(){

    }

    void GameEditor::render(void** data) {
        scene = EngineManager::getwlEngine()->getCurrentScene();
        ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;

        showGameWindow(data);
        showMenu();
        showAllGameObjects();
        showResourceWindow();

        removeGameObjects();
		removeComponents();
        dragDropGameObject();
    }
    
	void GameEditor::removeComponents() {
		for (size_t i = 0; i < componentToRemove.size(); i++) {
			removeComponent(componentToRemove[i].go, componentToRemove[i].component, componentToRemove[i].name);
		}
		componentToRemove.clear();
	}

    void GameEditor::removeGameObjects() {
        for(auto iter : objectToRemove) {
            scene->destroyGameObject(iter);
            if(iter == selectedGameObject) selectedGameObject = nullptr;
        }
        objectToRemove.clear();
    }

    void GameEditor::showGameWindow(void** data) {
        auto& style = ImGui::GetStyle();
        auto windowPadding = style.WindowPadding;
        style.WindowPadding = {0,0};
        std::string windowName;
        if (Settings::engineMode == Settings::EngineMode::Gameplay) windowName = "Game: GamePlay###";
        else windowName = "Game: Editor###";
        ImGui::Begin(windowName.data(),nullptr, ImGuiWindowFlags_NoResize);
        updateMouseInput();
        float sceneWidth = *(int*)(data[1]);
        float sceneHeight = *(int*)(data[2]);
        ImGui::Image((void*)*(unsigned int*)(data[0]), {sceneWidth,sceneHeight}, {0,1}, {1,0});//one commnet from imgui.cpp: my_void_ptr = (void*)(intptr_t)my_tex;                  // cast a GLuint into a void* (we don't take its address! we literally store the value inside the pointer)
        dragSprite();
        ImGui::End();
        
        //
        style.WindowPadding = windowPadding;
    }

    void GameEditor::showAllGameObjects() {
        ImGui::Begin("Scene Graph", nullptr, ImGuiWindowFlags_None);
        auto gameObjects = scene->getSceneGraph();
		dropSprite(nullptr);
        if(ImGui::BeginDragDropTarget()) {
            if(const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("GameObject")) {
                goPack.child = *static_cast<GameObject**>(payload->Data);
                goPack.parent = nullptr;
                goPack.dropped = true;
            } 
            ImGui::EndDragDropTarget();
        }
        pushGameObject(gameObjects->begin(), gameObjects);
        ImGui::End();
        showGameObjectInfo();
    }

    void GameEditor::pushGameObject(std::set<GameObject*>::iterator iter, const std::set<GameObject*>* gameObjects) {
        if(iter != gameObjects->end()) {
            bool open = ImGui::TreeNodeEx((*iter)->name.c_str(), ImGuiTreeNodeFlags_OpenOnArrow);

            //dragNdrop to change scene hierachy
            if(ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID)){
                ImGui::SetDragDropPayload("GameObject", &*iter, sizeof(GameObject*));
                ImGui::Text("%s", (*iter)->name.c_str());
                ImGui::EndDragDropSource();
            }
            if(ImGui::BeginDragDropTarget()) {
                if(const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("GameObject")) {
                    goPack.child = *static_cast<GameObject**>(payload->Data);
                    goPack.parent = *iter;
                    goPack.dropped = true;
                } 
                ImGui::EndDragDropTarget();
            }

            dropSprite(*iter); 

            //select game object
            if(ImGui::IsItemClicked() && (ImGui::GetMousePos().x - ImGui::GetItemRectMin().x) > ImGui::GetTreeNodeToLabelSpacing()) {
                selectedGameObject = *iter;
            }

            //gameobject little menu
            if (ImGui::BeginPopupContextItem())
            {
                if(ImGui::TreeNodeEx("Add Script")) {
                    for (auto f : *Component::componentFactoryList) {
                        auto componentIter = Component::getComponentIdToName()->find(f.first); // only Scripts are in componentIdToName
                        if (componentIter != Component::getComponentIdToName()->end()) {
                            std::string componentName = (*Component::getComponentIdToName()).at(f.first);
                            if (ImGui::MenuItem(componentName.data())) {
                                Json j;
                                j[componentName] = Json::array();
                                scene->addComponent(*iter, j);
                                scene->sceneData.addComponent(*iter, j);
                            }
                        }
                    }
                    ImGui::TreePop();
                }
                //remove gameobject
                if(ImGui::MenuItem("Remove")) {
                    objectToRemove.insert(*iter);
                }
                ImGui::EndPopup();
            }

            if(open) {
                pushGameObject((*iter)->children.begin(), &(*iter)->children);
                ImGui::TreePop();
            }
            pushGameObject(++iter, gameObjects);

        }
    }

    void GameEditor::showComponent(GameObject* go, Component* c, const std::string& name, std::function<void(GameObject*)> f){

        bool open = ImGui::TreeNodeEx(name.data());
        if (ImGui::BeginPopupContextItem())
        {
            //remove component
            if(ImGui::MenuItem("Remove")) {
                componentToRemove.push_back(ComponentRemovePack{go, c, name});
            }
            ImGui::EndPopup();
        }
        if(open){
            if(f) f(go);   
            ImGui::TreePop();
        }
    }

    void GameEditor::showGameObjectInfo() {
        ImGui::Begin("GameObject");
        if(selectedGameObject) {
            GameObject* go = selectedGameObject;
            char name[512];
            strcpy(name, go->name.data());
            if(ImGui::InputText("Object Name", name, 512)) {
                go->name = name;
                scene->sceneData.getData(go)["name"] = name;
            }
            for (auto& c : go->components) {
                if (c->getId() == Transform::componentId)showComponent(go, c.get(), "Transform", std::bind(&GameEditor::showTransformInfo, this, std::placeholders::_1));
                //else if (c->getId() == Sprite::componentId)showComponent(go, c.get(), "Sprite", std::bind(&GameEditor::showSpriteInfo, this, std::placeholders::_1));
                //else if (c->getId() == Animation::componentId)showComponent(go, c.get(), "Animation", std::bind(&GameEditor::showAnimationInfo, this, std::placeholders::_1));
                else {
                    std::size_t t = c->getId();
                    auto* s = Component::getComponentIdToName();
                    auto iter = Component::getComponentIdToName()->find(t);
                    if (iter != Component::getComponentIdToName()->end()) {
                        ImGui::TreeNodeEx(iter->second.data(), ImGuiTreeNodeFlags_Leaf);
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
                ImGui::MenuItem("New Scene", "CTRL+N");
                if (ImGui::IsItemClicked()) {
                    std::string filePath = "../mainScene";
                    while (std::ifstream(filePath)) {
                        filePath += " New";
                    }
                    std::ofstream ofs;
                    ofs.open(filePath);
                    if (ofs.good()) {
                        GameObject* nil = nullptr;
                        ofs << "{\"gameObjects\": {\"1\" : {\"children\": [] , \"components\" : {\"Camera2D\": [] , \"Transform\" : [0.0, 0.0, 1000] }, \"name\" : \"Camera\", \"parent\" :" + Utility::toPointerString(nil) + "}} }";
                    }
                    ofs.close();
                }
                ImGui::MenuItem("Save", "CTRL+S");
                if (ImGui::IsItemClicked()) {
                    const nlohmann::json& scene_jsonRef = scene->sceneData.data;
                    std::ofstream ofs;
                    ofs.open(scene_jsonRef["scene_path"].get<std::string>());
                    if (ofs.good()) {
                        ofs << scene_jsonRef.dump();
                    }
                    ofs.close();
                }
                ImGui::MenuItem("Reload", "CTRL+S");
                if (ImGui::IsItemClicked()) {
                    scene->loadScene(scene->filePath);
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

    void GameEditor::showAnimationInfo(GameObject* go){
        auto animation = go->getComponent<Animation>();
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
        bool inputX = ImGui::InputFloat("local x", &pos.x);
        bool inputY = ImGui::InputFloat("local y", &pos.y);
        bool inputZ = ImGui::InputFloat("local z", &pos.z);
        if ( inputX|| inputY || inputZ) {
            transform->setLocalPosition(pos);
            Json& json = scene->sceneData.getData(go);
            json["components"]["Transform"][0] = pos.x;
            json["components"]["Transform"][1] = pos.y;
            json["components"]["Transform"][2] = pos.z;
        }

        float scale_f = transform->scale.x;
        if (ImGui::InputFloat("Scale Aspect Ratio", &scale_f)) {
            transform->setScale(scale_f, scale_f, scale_f);
        }
    }

    void GameEditor::showResourceWindow() {
        ImGui::Begin("Resource",nullptr,ImGuiWindowFlags_HorizontalScrollbar);
        showResourceInDirectory("../resource");
        ImGui::End();
    }

    void GameEditor::showSpriteInfo(GameObject* go) {
        auto sprite = go->getComponent<Sprite>();
        ImGui::Image((void*)sprite->texture->mTexture, {(float)sprite->texture->mWidth, (float)sprite->texture->mHeight}, {0,1}, {1,0});
    }
    void GameEditor::showResourceInDirectory(const std::string& path) {
        DIR *dir;
        struct dirent *ent;
        /* Open directory stream */
        dir = opendir (path.data());
        if (dir != NULL) {
            if(ImGui::TreeNodeEx(path.data())){
                std::vector<std::string> directory;
                std::vector<std::string> files;
                while ((ent = readdir (dir)) != NULL) {
                    switch (ent->d_type) {
                        case DT_REG:{
                            files.push_back(path + "/" + ent->d_name);
                            break;
                        }

                        case DT_DIR:
                            if(ent->d_name[0] != '.')
                                directory.push_back(path+"/"+ent->d_name);
                            break;

                        default:
                            printf ("%s*\n", ent->d_name);
                    }
                }

                for (auto& dir : directory) {
                    showResourceInDirectory(dir);
                }
                for (auto& filePath : files) {
                    std::size_t dotPos = filePath.find_last_of('.');
                    std::string etx = filePath.substr(dotPos+1, filePath.length());
                    std::transform(etx.begin(), etx.end(), etx.begin(), [](unsigned char c) {return std::tolower(c); });
                    if (etx == "png" || etx == "jpg") {
                        std::string name = filePath.substr(filePath.find_last_of("/") + 1, filePath.length());
                        if (ImGui::TreeNodeEx(name.data())) {
                            auto texture = ResourceManager::get()->getTexture(filePath);
                            ImGui::Image((void*)texture->mTexture, {(float)texture->mWidth, (float)texture->mHeight}, {0,1}, {1,0});
                            ImGui::TreePop();
                        }
                        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
                        {
                            Texture* texture = ResourceManager::get()->getTexture(filePath);
                            ImGui::SetDragDropPayload("Sprite", &texture, sizeof(Texture*));        // Set payload to carry the index of our item (could be anything)
                            ImGui::Text("%s", filePath.data());
                            ImGui::EndDragDropSource();
                        }
                    }
                }
                ImGui::TreePop();
            }

            closedir (dir);

        } else {
            std::cerr << "Resource Manager path error\n";
        }
    }

    void GameEditor::dropSprite(GameObject* parent) {
        if (ImGui::BeginDragDropTarget()){
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Sprite")){
                Texture* texture_ptr = *static_cast<Texture**>(payload->Data);
                Json go_json;
                go_json["name"] = texture_ptr->sourcePath.substr(texture_ptr->sourcePath.find_last_of("/")+1, texture_ptr->sourcePath.size() - 4); // being lazy here, -4 becuase .jpg and .png all have 4 characters
                go_json["components"] = Json::object();
                go_json["children"] = json::array();
                Json spriteParams = Json::array({ texture_ptr->sourcePath ,"sprite_shader"});
                Json transformParams = Json::array({0,0,0});
                go_json["components"]["Sprite"] = spriteParams;
                go_json["components"]["Transform"] = transformParams;

                scene->createGameObject(go_json, parent);
            }
            ImGui::EndDragDropTarget();
        }
    }

    void GameEditor::dragDropGameObject() {
        if(goPack.dropped) {
            goPack.child->setParent(goPack.parent);
            goPack.dropped = false;
        }
    }

    void GameEditor::removeComponent(GameObject* go, Component* c, const std::string& name) {
        go->removeComponent(c);
        scene->sceneData.removeComponent(go, name);
    }

    void GameEditor::updateMouseInput() {
        auto inputSystem = InputSystem::get();

        auto pos = ImGui::GetWindowPos();
        inputSystem->setGameplayWindowOffset(pos.x, pos.y);
    }

    void GameEditor::dragSprite() {
        static Transform* target = nullptr;
        if(ImGui::IsWindowFocused()) {
            auto inputSystem = InputSystem::get();
            int mouseX, mouseY;
            if(inputSystem->mouseClickedOnScene(mouseX, mouseY, Button::Left)) {
                auto go = scene->findGameObjectNear(mouseX, mouseY);
                if(go && !target) {
                    target = go->getComponent<Transform>();
                    selectedGameObject = go;
                }

            }
            else {
                target = nullptr;
            }
            if (target) {
                target->setPosition({ mouseX, mouseY, 0 });
            }
        }
    }
}
