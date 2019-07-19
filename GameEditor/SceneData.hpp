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
        void createGameObject(GameObject*, GameObject*, const Json*);
		void clear();
		void destroyGameObject(GameObject*);
        void removeComponent(GameObject*, const std::string&);

		//json is an array of json object
        void addComponent(GameObject*, const Json&);
        void changeHierachy(GameObject* child, GameObject* parent);
        void editTransform(GameObject*, const int& x, const int& y, const int& z);
		Json& getData(GameObject*);
    private:
        void eraseGameObjectFromChildren(const std::string& parent, const std::string& child);
		
		
    };
}
#endif

