#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <set>

#include "Transform.hpp"

#include "../Graphics/Texture.hpp"
#include "Animation.hpp"
namespace wlEngine {
    class GameObject {
    public:
        GameObject();

        //Transform
        bool moveToParent(GameObject*);
        void loadTexture(const char* path);
        void setPosition(const float& x,const float& y,const float& z);
        void moveBy(const float& x, const float& y, const float& z);
        void setLocalPosition(const float& x, const float& y, const float& z);

        //Animation
        void loadClips(const char* path);
        void playAnimation(const char* name);
    protected:
        uint tag; 

        Texture* texture;
        Transform transform;
        Animation animation;

        GameObject* parent;
        std::set<GameObject*> children;

        virtual void update();
        virtual void render();

        friend class Scene;
    };
}
#endif
