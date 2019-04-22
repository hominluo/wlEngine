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
        void setTag(int);
        glm::vec3 getSize();

        ///Transform
        /**
         * @brief move this gameObject to @param GameObject which is the parent
         *
         * @param GameObject the parent
         *
         * @return true if successfully move to the paretn
         */
        bool moveToParent(GameObject*);
        void loadTexture(const char* path);
        void setPosition(const float& x,const float& y,const float& z);
        void moveBy(const float& x, const float& y, const float& z);
        void setLocalPosition(const float& x, const float& y, const float& z);
        glm::vec3 getPosition();
        glm::vec3 getLocalPosition();

        //Animation
        void loadClips(const char* path);
        void playAnimation(const char* name);

        //RigidBody
        void setRigidBody(b2Body* body);
        void setGravity(bool);
        void setVelocity(const float& x, const float& y, const float& z);
        void createFixture(b2FixtureDef& def);
        void setContactBeginCallback(std::function<void()>&&);
        void setContactEndCallback(std::function<void()>&&);
        glm::vec3 getLinearVelocity();
    protected:
        unsigned int tag; 
        Transform transform;

        Texture* texture;
        Animation* animation;
        RigidBody mRigidBody;

        GameObject* parent;
        std::set<GameObject*> children;

        virtual void update();
        virtual void render();



        friend class Scene;

    private:
        void updateWorldPosition(); 

        /* convert to down_left origin, and convert from 3d to 2d space*/
        glm::vec3 calculateRenderPosition();
    };
}
#endif
