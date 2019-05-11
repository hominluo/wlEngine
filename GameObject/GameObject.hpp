#pragma once
#include "Component/Component.hpp"
#include "Component/Texture.hpp"
#include "Component/Transform.hpp"
#include <set>
#include <memory>

namespace wlEngine {
    class GameObject {
    public:
        GameObject() = default;
        ~GameObject() = default;
        std::set<GameObject*> children;
        GameObject* parent = nullptr;
        std::set<std::shared_ptr<Component>> components;
        
        template <typename ComponentType, typename... Args>
		ComponentType* addComponent(Args&& ... params);
        
        template <typename ComponentType>
        void addComponent(std::shared_ptr<ComponentType> );
        
        template <typename ComponentType>
        void removeComponent();

        template <typename ComponentType>
        ComponentType* getComponent();

        virtual void update(){
            //updateWorldPosition(); has some problem when applied to camera

            for (auto iter = children.begin(); iter != children.end(); iter++) {
                (*iter)->update();
            }
        }
        virtual void render(){
            auto texture = getComponent<Texture>();
            if (!texture) return;

            //auto currentClip = animation ? animation->getCurrentClip() : nullptr;
            texture->render(getComponent<Transform>()->getModel());

            for (auto iter = children.begin(); iter != children.end(); iter++) {
                (*iter)->render();
            }
        }
    };

    template<typename ComponentType, typename... Args>
	ComponentType* GameObject::addComponent(Args&&... params) {
		auto p = ComponentType::createComponent(this, params...);
		auto raw = p.get();
        components.emplace(std::move(p));
		return raw;
    }

    template <typename ComponentType>
    ComponentType* GameObject::getComponent() {
        for (auto& c : components) {
            if (c->isType(ComponentType::componentId)) {
                return static_cast<ComponentType*>(c.get());
            }
            
        }

        return nullptr;
    }

    template <typename ComponentType>
    void GameObject::addComponent(std::shared_ptr<ComponentType> c) {
        c->gameObject = this;
        components.insert(c);
    }

    template <typename ComponentType>
    void GameObject::removeComponent() {
        for (auto& c : components) {
            if (c->isType(ComponentType::componentId)) {
                components.erase(c);
                return;
            }
        }
    }
}
