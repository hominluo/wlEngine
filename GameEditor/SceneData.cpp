#include "SceneData.hpp"
#include "../Utility/Utility.hpp"
#include <sstream>

namespace wlEngine {

    void SceneData::createGameObject(GameObject* go, GameObject* parent, const Json* json_ptr){
		nlohmann::json j;
		
		if (json_ptr == nullptr) {
			j["name"] = go->name;
			j["components"] = nlohmann::json();
			j["children"] = json::array();
			json_ptr = &j;
		}
		
		std::string goId = Utility::toPointerString(go);
        data["gameObjects"][goId] = *json_ptr;

		std::string parentId = Utility::toPointerString(parent);
        data["gameObjects"][goId]["parent"] = parentId;
		if(parent) data["gameObjects"][parentId]["children"].push_back(goId);
    }

    void SceneData::addSprite(GameObject* go, const std::string& sourcePath, const std::string& shader) {
        Json& json = getData(go);
        nlohmann::json sprite_json = nlohmann::json::array();
        sprite_json.push_back(sourcePath);
        sprite_json.push_back(shader);
        json["components"]["Sprite"] = sprite_json;
    }

    void SceneData::addTransform(GameObject* go){
        Json& json = getData(go);
        nlohmann::json transforom_json = nlohmann::json::array();
        transforom_json.push_back(0);
        transforom_json.push_back(0);
        transforom_json.push_back(0);
        json["components"]["Transform"] = transforom_json;
    }

	void SceneData::clear() {
		data.clear();
	}

	void SceneData::destroyGameObject(GameObject* go) {
		std::string goId = Utility::toPointerString(go);

		if (go->parent) {
			std::string parent = Utility::toPointerString(go->parent);
			auto& children = data["gameObjects"][parent]["children"];
			for (auto iter = children.begin(); iter != children.end(); ++iter) {
				if (*iter == goId) {
					children.erase(iter - children.begin());
					break;
				}
			}
		}
        
		auto children = data["gameObjects"][goId]["children"];
		for (auto iter = children.begin(); iter != children.end(); ++iter) {
			data["gameObjects"].erase(iter->get<std::string>());
		}

		data["gameObjects"].erase(goId);
	}

	Json& SceneData::getData(GameObject* go) {
		return data["gameObjects"][Utility::toPointerString(go)];
	}

    void SceneData::removeComponent(GameObject* go, const std::string& c) {
        std::string goId = Utility::toPointerString(go);
        auto& components = data["gameObjects"][goId]["components"];
        for (auto iter = components.begin(); iter != components.end(); ++iter) {
            if (iter.key() == c) {
                components.erase(iter.key());
                break;
            }
        }
    }

    void SceneData::addComponent(GameObject* go, const Json& json) {
        auto goId = Utility::toPointerString(go);
        for (auto iter = json.begin(); iter != json.end(); ++iter){
            data["gameObjects"][goId]["components"][iter.key()] = iter.value();
        }
    }
}
