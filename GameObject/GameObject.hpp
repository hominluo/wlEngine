#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <set>
#include <glm/vec3.hpp>

#include "Transform.hpp"
#include "RigidBody.hpp"

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
        glm::vec3 getPosition();
        glm::vec3 getLocalPotion();

        //Animation
        void loadClips(const char* path);
        void playAnimation(const char* name);

        //RigidBody
        void setGravity(bool);
        void setVelocity(const float& x, const float& y, const float& z);
        glm::vec3 getVelocity();
    protected:
        uint tag; 
        Transform transform;
        RigidBody rigidBody;

        Texture* texture;
        Animation* animation;

        GameObject* parent;
        std::set<GameObject*> children;

        virtual void update();
        virtual void render(const int& x, const int& y, const int& z);

        /* convert to down_left origin, and convert from 3d to 2d space*/
        glm::vec3 calculateRenderPosition(const glm::vec3& cameraPos);


        friend class Scene;
    };
}
#endif
