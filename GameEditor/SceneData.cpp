#include "SceneData.hpp"
#include "../Utility/Utility.hpp"
#include <sstream>

namespace wlEngine {

    void SceneData::createGameObject(GameObject* go, GameObject* parent, const Json* json_ptr){
		nlohmann::json j;
		
		if (json_ptr == nullptr) {
			j["name"] = go->name;
			j["components"] = Json::array();
			j["children"] = Json::array();
			json_ptr = &j;
		}
		
		std::string goId = Utility::toPointerString(go);
        data["gameObjects"][goId] = *json_ptr;
        data["gameObjects"][goId]["children"] = Json::array();

		std::string parentId = Utility::toPointerString(parent);
        data["gameObjects"][goId]["parent"] = parentId;
		if(parent) data["gameObjects"][parentId]["children"].push_back(goId);
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
            if ((*iter)["name"] == c) {
                components.erase(iter);
                break;
            }
        }
    }
    void SceneData::eraseGameObjectFromChildren(const std::string& parent, const std::string& child) {
        auto& children = data["gameObjects"][parent]["children"];
        for (auto iter = children.begin(); iter != children.end(); ++iter) {
            if (*iter == child) {
                children.erase(iter);
                break;
            }
        }
    }

    void SceneData::addComponent(GameObject* go, const Json& json) {
        auto goId = Utility::toPointerString(go);
        for (auto iter = json.begin(); iter != json.end(); ++iter){
            *Utility::findComponentWithName(data["gameObjects"][goId],iter.key()) = iter.value();
        }
    }

    void SceneData::changeHierachy(GameObject* parent, GameObject* child) {
        auto parentId = Utility::toPointerString(parent);
        auto childId = Utility::toPointerString(child);
        if(child->parent) {
            eraseGameObjectFromChildren(Utility::toPointerString(child->parent), childId);
        }

        data["gameObjects"][childId]["parent"] = parentId;
        data["gameObjects"][parentId]["children"].push_back(childId);
    }



    void SceneData::editTransform(GameObject* go, const int& x, const int& y, const int& z) {
        auto goId = Utility::toPointerString(go);
		auto& t = (*Utility::findComponentWithName(data["gameObjects"][goId], "Transform"))["params"];
        t[0] = x;
        t[1] = y;
        t[2] = z;
    }
}
