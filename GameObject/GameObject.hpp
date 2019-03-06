#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <set>

#include "Transform.hpp"

#include "../Graphics/Texture.hpp"
namespace wlEngine {
    class GameObject {
    public:
        GameObject();

        bool moveToParent(GameObject*);

        void loadTexture(const char* path);
        void setPosition(float x, float y, float z);
        void setLocalPosition(float x, float y, float z);
    protected:
        uint tag; 

        Texture* texture;
        Transform* transform;

        GameObject* parent;
        std::set<GameObject*> children;

        void update();
        void render();

        friend class Scene;
    };
}
#endif
