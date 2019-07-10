#include "SceneData.hpp"

namespace wlEngine {

    void SceneData::createGameObject(GameObject* go, GameObject* parent, Json* json_ptr){
		nlohmann::json j;
		size_t index = 0;
		
		if (json_ptr == nullptr) {
			j["name"] = go->name;
			j["components"] = nlohmann::json();
			j["children"] = json::array();
			json_ptr = &j;
		}
		
		if (parent) {
			auto& children = getData(parent)["children"];
			children.push_back(*json_ptr);
			json_ptr = &children.back();
			index = children.size();
		}
		else {
			auto& scene_graph = data["scene_graph"];
			scene_graph.push_back(*json_ptr);
			json_ptr = &scene_graph.back();
			index = scene_graph.size();
		}

		//build json pointer
		if (parent) {
			auto parent_ptr = gameObjectData[parent];
			auto parent_str = parent_ptr.to_string();
			gameObjectData[go] = Json::json_pointer(parent_str + "/children/" + std::to_string(index));
		}
		else {
			gameObjectData[go] = Json::json_pointer("/scene_graph/" + std::to_string(index));
		}
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
		gameObjectData.clear();
		data.clear();
	}

	void SceneData::destroyGameObject(GameObject* go) {
		data.erase(gameObjectData[go]);
	}

	Json& SceneData::getData(GameObject* go) {
		return data[gameObjectData[go]];
	}
}
