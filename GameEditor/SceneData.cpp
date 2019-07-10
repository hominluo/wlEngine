#include "SceneData.hpp"

namespace wlEngine {

    void SceneData::createGameObject(GameObject* go, GameObject* parent, Json* json_ptr){
		if (json_ptr == nullptr) {
			nlohmann::json j;
			j["name"] = go->name;
			j["components"] = nlohmann::json();
			j["children"] = json::array();
			json_ptr = &j;
		}
		if (parent) {
			auto children = (*gameObjectData[parent])["children"];
			children.push_back(*json_ptr);
			json_ptr = &(*(children.end() - 1));
		}
		else {
			auto& scene_graph = data["scene_graph"];
			scene_graph.push_back(*json_ptr);
			json_ptr = &*(scene_graph.end() - 1);
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

	void SceneData::clear() {
		gameObjectData.clear();
		data.clear();
	}

	void SceneData::destroyGameObject(GameObject* go) {
		auto j_go = gameObjectData[go];
		if (auto parent = go->parent) {
			auto& j_parent = *gameObjectData[parent];
			Json::iterator iter = j_parent["children"].begin();
			Json::iterator end = j_parent["children"].end();
			for (; iter != end; ++iter) {
				if (&*iter == j_go) break;
			}
			if (iter == end) assert(0 && "parent doesn't have this child");
			j_parent["children"].erase(iter);
		}
		else {
			Json::iterator iter = data["scene_graph"].begin();
			Json::iterator end = data["scene_graph"].end();
			for (; iter != end; ++iter) {
				if (&*iter == j_go) break;
			}
			if (iter == end) {
				assert(0 && "scene doesn't have this gameObject");

			}
			data["scene_graph"].erase(iter);
		}
		gameObjectData.erase(go);
	}
}
