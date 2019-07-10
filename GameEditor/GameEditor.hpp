#pragma once
#include <SDL_events.h>
#include <string>
#include <json.hpp>
#include "../GameObject/Scene.hpp"
using json = nlohmann::json;
namespace wlEngine {
    class GameObject;
    class Sprite;
    class Animation;
    class GameEditor {
    public:
        GameEditor();
        ~GameEditor();

        /**
         * @brief called by UISystem
         */
        void render(void** data);

        void loadScene(const std::string&);

    private:
        GameObject* selectedGameObject;
        Scene* scene;

        void showGameObjectInfo();
        void showAllGameObjects();
        void pushGameObject(std::set<GameObject*>::iterator iter, const std::set<GameObject*>* gameObjects);

        void showMenu();

        void showAnimationInfo(Animation*);
        void showTransformInfo(GameObject*);
        void showSpriteInfo(Sprite*);

        void showGameWindow(void** data);

        void showResourceWindow();
        void showResourceInDirectory(const std::string& path);
        void dropSprite(GameObject* parent);
    };
}
