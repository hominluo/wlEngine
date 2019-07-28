#pragma once
#include <SDL_events.h>
#include <string>
#include <json.hpp>
#include "../GameObject/Scene.hpp"
using json = nlohmann::json;
namespace wlEngine {
    class Entity;
    class Sprite;
    class Animation;
    struct GameObjectPack {
        Entity* child = nullptr;
        Entity* parent = nullptr;
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
        Entity* selectedGameObject;
        Scene* scene;
        float gameplayWindowOffsetX;
        float gameplayWindowOffsetY;

        void showGameObjectInfo();
        void showAllGameObjects();
        void pushGameObject(std::set<Entity*>::iterator iter, const std::set<Entity*>* gameObjects);
        /**
         * @brief draw to change the scene hierachy
         *
         * @param parent
         */
        void dragDropGameObject();
        GameObjectPack goPack;

        void showMenu();

        void showComponent(Entity*, Component*, const std::string& name, std::function<void(Entity*)>);
        void showAnimationInfo(Entity*);
        void showTransformInfo(Entity*);
        void showSpriteInfo(Entity*);

        void showGameWindow(void** data);

        void showResourceWindow();
        void showResourceInDirectory(const std::string& path);
        void dropSprite(Entity* parent);

        /**
         * @brief we can't remove game object when they are being iterating, this function is called
         * after all the rendering and operation
         */
        void removeGameObjects();
        std::set<Entity*> objectToRemove;

        void removeComponent(Entity* go, Component*, const std::string& name);
		void removeComponents();
		struct ComponentRemovePack {
			Entity* go;
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
