#include "GameObject.hpp"

#include "../Time.hpp"
namespace wlEngine {
    GameObject::GameObject(): texture(nullptr), animation(nullptr), parent(nullptr) {

    }

    void GameObject::update() {
        //update transformation according to the object's b2Body and zMovement
        auto position = transform.getPosition();
        auto zMovement = mRigidBody.getZMovement();
        position.z += zMovement;
        if (mRigidBody.hasBody()) {
            auto bodyPosition = mRigidBody.getPosition();
            position.x = bodyPosition.x;
            position.y = bodyPosition.y;
        }
        setPosition(position.x, position.y, position.z);
        mRigidBody.update(getLocalPosition().z);

		for (auto iter = children.begin(); iter != children.end(); iter++) {
			(*iter)->update();
		}
    }

    bool GameObject::moveToParent(GameObject* parent) {
        this->parent = parent;

        parent->children.insert(this);
        return true;
    }

    void GameObject::render(const int& x, const int& y, const int& z) {
        if (!texture) return;

        glm::vec3 position = calculateRenderPosition(glm::vec3{x, y, z});

        auto currentClip = animation ? animation->getCurrentClip() : nullptr;
        texture->render(position.x, position.y, currentClip);

        for (auto iter = children.begin(); iter != children.end(); iter++) {
            (*iter)->render(x, y, z);
        }
    }

    void GameObject::loadTexture(const char* path) {
        if (!texture) texture = new Texture();

        texture->loadFromFile(path);
    }

    void GameObject::setPosition(const float& x, const float& y,const float& z){
        glm::vec3 newPosition{x,y,z};
        glm::vec3 moveVector = newPosition - getPosition();

        transform.setPosition(x, y, z);

        for (auto iter = children.begin(); iter != children.end(); iter++) {
            (*iter)->moveBy(moveVector.x, moveVector.y, moveVector.z);
        }
    }

    void GameObject::setLocalPosition(const float& x, const float& y, const float& z) {
        glm::vec3 newLocalPosition{x,y,z};
        glm::vec3 newPosition = parent->getPosition() + newLocalPosition;
        glm::vec3 moveVector = newPosition - getPosition();

        transform.setPosition(newPosition.x, newPosition.y, newPosition.z);

        for (auto iter = children.begin(); iter != children.end(); iter++) {
            (*iter)->moveBy(moveVector.x, moveVector.y, moveVector.z);
        }
    }

    void GameObject::moveBy(const float& x, const float& y, const float& z) {
        transform.moveBy(x, y, z);

        for (auto iter = children.begin(); iter != children.end(); iter++) {
            (*iter)->moveBy(x, y, z);
        }
    }
    void GameObject::loadClips(const char* path) {
        if (!animation) animation = new Animation;
        animation->loadClips(path);
    }

    void GameObject::playAnimation(const char* name) {
        animation->playAnimation(name);
    }

    glm::vec3 GameObject::calculateRenderPosition(const glm::vec3& cameraPos) {
        glm::vec3 position = transform.getPosition();

        position.y = -position.y;
        position.y -= texture->getHeight();

        position.y -= 1 * position.z;

        return position - cameraPos;
    }

    glm::vec3 GameObject::getPosition() {
        return transform.getPosition();
    }

    glm::vec3 GameObject::getLocalPosition() {
        if (parent) return getPosition() - parent->getPosition();
        else return getPosition();
    }

    void GameObject::setGravity(bool has) {
        mRigidBody.setGravity(has);
    }
    void GameObject::setVelocity(const float& x, const float& y, const float& z) {
        mRigidBody.setVelocity(x,y,z);
    }

    void GameObject::setRigidBody(b2Body* body) {
        mRigidBody.setBody(body);
    }

    void GameObject::createFixture(b2FixtureDef& def) {
        mRigidBody.createFixture(def);
    }
}

