#pragma once

#include <SDL_events.h>
#include <set>
namespace wlEngine {
    class GameObject;
    class DeveloperUI {
    public:
        DeveloperUI();
        ~DeveloperUI();

        /**
         * @brief called by UISystem
         */
        void render();

    private:
        GameObject* selectedGameObject;

        void showAllGameObjects();
        void pushGameObject(std::set<GameObject*>::iterator iter, const std::set<GameObject*>* gameObjects);
        void showGameObjectInfo();
    };
}
