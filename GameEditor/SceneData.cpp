#include "SceneData.hpp"

namespace wlEngine {

    void SceneData::createGameObject(GameObject* go, GameObject* parent, Json* json_ptr){
        if (json_ptr == nullptr) {
            nlohmann::json j;
            j["name"] = go->name;
            j["components"] = nlohmann::json();
            j["children"] = json::array();
            if(parent){
                auto children = (*gameObjectData[parent])["children"];
                children.push_back(j);
                json_ptr = &(*(children.end() - 1));
            }
            else {
                auto& scene_graph = data["scene_graph"];
				scene_graph.push_back(j);
                json_ptr = &*(scene_graph.end() - 1);
            }
        }

        gameObjectData[go] = json_ptr;
    }

    void SceneData::addSprite(GameObject* go, const std::string& sourcePath, const std::string& shader) {
        Json& json = *gameObjectData[go];
        nlohmann::json sprite_json = nlohmann::json::array();
        sprite_json.push_back(sourcePath);
        sprite_json.push_back(shader);
        json["components"]["Sprite"] = sprite_json;
    }

    void SceneData::addTransform(GameObject* go){
        Json& json = *gameObjectData[go];
        nlohmann::json transforom_json = nlohmann::json::array();
        transforom_json.push_back(0);
        transforom_json.push_back(0);
        transforom_json.push_back(0);
        json["components"]["Transform"] = transforom_json;
    }
}
