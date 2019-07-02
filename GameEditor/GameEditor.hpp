#pragma once

#include <SDL_events.h>
#include <set>
#include <string>
#include <json.hpp>

using json = nlohmann::json;
namespace wlEngine {
    class GameObject;
    class GameEditor {
    public:
        GameEditor();
        ~GameEditor();

        /**
         * @brief called by UISystem
         */
        void render();

        void loadScene(const std::string&);

    private:
        GameObject* selectedGameObject;
        json currentScene;

        void showAllGameObjects();
        void pushGameObject(std::set<GameObject*>::iterator iter, const std::set<GameObject*>* gameObjects);
        void showGameObjectInfo();
        void showMenu();
    };
}
