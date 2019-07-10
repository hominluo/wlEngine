#pragma once
#include "../Settings.hpp"

#if SETTINGS_ENGINEMODE
#include<map>
#include<json.hpp>
#include"../GameObject/GameObject.hpp"

namespace wlEngine {
    using Json = nlohmann::json;
    enum class EditableComponent {
        Sprite, Transform        
    };
    class SceneData {
    public:
        Json data;
        void createGameObject(GameObject*, GameObject*, Json*);
        void addSprite(GameObject* go, const std::string& sourcePath, const std::string& shader);
        void addTransform(GameObject* go);
        void setCamera();
		void clear();
		void destroyGameObject(GameObject*);
		Json& getData(GameObject*);
	private:
		std::map<GameObject*, Json::json_pointer> gameObjectData;
		
    };
}
#endif

