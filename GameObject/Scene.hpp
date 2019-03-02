#ifndef SCENE_H
#define SCENE_H
#include <set>
#include <SDL.h>

#include "../GameObject/GameObject.hpp"
#include "../Graphics/Texture.hpp"

namespace wlEngine {
    class Scene {
        public:
            Scene();
            ~Scene();
            void update();
            void addGameObject(GameObject*);
            void loadTexture(const char*);

            void setRendererColor(const Uint8&, const Uint8&, const Uint8&, const Uint8&);
        private:
            Texture* texture;
            SDL_Renderer* sceneRenderer;
            std::set<GameObject*> gameObjects;

            void render();

            friend class EngineManager;
    };
}

#endif
