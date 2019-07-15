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

        void showComponent(GameObject*, Component*, const std::string& name, std::function<void(GameObject*)>);
        void showAnimationInfo(GameObject*);
        void showTransformInfo(GameObject*);
        void showSpriteInfo(GameObject*);

        void showGameWindow(void** data);

        void showResourceWindow();
        void showResourceInDirectory(const std::string& path);
        void dropSprite(GameObject* parent);

        /**
         * @brief we can't remove game object when they are being iterating, this function is called
         * after all the rendering and operation
         */
        void removeGameObjects();
        std::set<GameObject*> objectToRemove;

        void removeComponent(GameObject* go, Component*, const std::string& name);
		void removeComponents();
		struct ComponentRemovePack {
			GameObject* go;
			Component* component;
			std::string name;
		};
		std::vector<ComponentRemovePack> componentToRemove;

        /**
         * @brief used when in engine is in Editor mode to update the mouse click location in Gameplay window,
         * this is based on get window location, so it has to be called after the initialization of Gameplay window
         */
        void updateMouseInput();


        void dragSprite();
    };
}
