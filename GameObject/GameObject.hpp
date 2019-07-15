#pragma once
#include "../Component/Component.hpp"
#include <memory>
#include "../Settings.hpp"
namespace wlEngine {
    class Scene;
    class GameObject {
    public:
        GameObject(const std::string& name);
        ~GameObject();
        std::string name;
		std::set<GameObject*> children;

        GameObject* getParent() {return parent;}
        void setParent(GameObject*);
        void setParent(Scene*);

        std::set<std::shared_ptr<Component>> components;
        
        template <typename ComponentType, typename... Args>
		ComponentType* addComponent(Args&& ... params);

        template <typename ComponentType>
        void addComponent(std::shared_ptr<ComponentType>& );
        
        template <typename ComponentType>
        void removeComponent();

        template <typename ComponentType>
        ComponentType* getComponent();

        void removeComponent(Component* c);

    private:
        GameObject* parent = nullptr;
        friend class Transform;
        friend class SceneData;
    };

    template<typename ComponentType, typename... Args>
	ComponentType* GameObject::addComponent(Args&&... params) {
		auto p = ComponentType::createComponent(this, params...);
		auto raw = p.get();
        components.insert(p);
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
    void GameObject::addComponent(std::shared_ptr<ComponentType>& c) {
        if (c->gameObjects == nullptr) c->gameObject = this;
        else c->gameObjects.insert(this);

        components.insert(c);
    }

    template <typename ComponentType>
        void GameObject::removeComponent() {
            for (auto& c : components) {
                if (c->isType(ComponentType::componentId)) {
                    if (c->gameObjects) {
                        c->gameObjects->erase(this);
                    }
                    components.erase(c);
                    return;
                }
            }
        }
}
