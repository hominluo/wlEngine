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
        void setPosition(const float& x,const float& y,const float& z);
        void moveBy(const float& x, const float& y, const float& z);
        void setLocalPosition(const float& x, const float& y, const float& z);
    protected:
        uint tag; 

        Texture* texture;
        Transform* transform;

        GameObject* parent;
        std::set<GameObject*> children;

        virtual void update();
        virtual void render();

        friend class Scene;
    };
}
#endif
