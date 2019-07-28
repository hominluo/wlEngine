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
    struct GameObjectPack {
        GameObject* child = nullptr;
        GameObject* parent = nullptr;
        bool dropped = false;
    };
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
		/********************** Data ***************************/
        GameObject* selectedGameObject;
        Scene* scene;
        float gameplayWindowOffsetX;
        float gameplayWindowOffsetY;

        void showGameObjectInfo();
        void showAllGameObjects();
        void pushGameObject(std::set<GameObject*>::iterator iter, const std::set<GameObject*>* gameObjects);
        /**
         * @brief draw to change the scene hierachy
         *
         * @param parent
         */
        void dragDropGameObject();
        GameObjectPack goPack;

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

        void dragSprite();

		/*************************** Helper **********************************/
		/**
		 * @brief this function calculate the mouse click on scene (bottom-left being (0,0))
		 *
		 * @param x
		 * @param y
		 * @param Button right or left click
		 *
		 * @return
		 */
		bool mousePressingOnScene(int& x, int& y);
    };
}
