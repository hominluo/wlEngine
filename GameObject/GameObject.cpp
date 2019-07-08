#include "GameObject.hpp"
#include "../Component/Transform.hpp"
#include "Scene.hpp"
#include "../EngineManager.hpp"
namespace wlEngine {
    GameObject::GameObject(const std::string& name, GameObject* parent, nlohmann::json* json) : name(name), json_ptr(nullptr) {
        if (parent) {
            this->parent = parent;
            parent->children.insert(this);
        }
        else {
            auto scene = EngineManager::getwlEngine()->getCurrentScene();
            scene->addGameObject(this);
        }
#if SETTINGS_ENGINEMODE
        if (json == nullptr) {
            nlohmann::json j;
            j["name"] = name;
            j["components"] = nlohmann::json();
            j["children"] = json::array();
            if(parent){
                auto& json_parent = *parent->json_ptr;
                auto& children_parent = json_parent["children"];
                children_parent.push_back(j);
                auto iter = children_parent.end();
                --iter;
                json_ptr = &(*(iter));
            }
            else {
                auto scene = EngineManager::getwlEngine()->getCurrentScene();
                auto& scene_graph = scene->scene_json["scene_graph"];
                scene_graph.push_back(j);
                json_ptr = &*(scene_graph.end() - 1);
            }
        }
        else json_ptr = json;
#endif
    }

    void GameObject::setParent(Scene* scene) {
        scene->addGameObject(this);       
    }
    void GameObject::setParent(GameObject* go) {
        parent = go;
        go->children.insert(this);
    }

    GameObject::~GameObject() {
        for(auto& c : components) {
            c->destruct(this);
        }
    }

}
