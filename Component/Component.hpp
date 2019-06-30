#pragma once
#include <functional>
#include <memory>
#include <string>
#include <set>
#include <iostream>
#include <unordered_set>
#include <map>

#include "Memory.hpp"

#define COMPONENT_DECLARATION(P, T, N) \
    static const std::string name; \
    static const std::size_t componentId; \
    virtual bool isType(const std::size_t& typeId) const override; \
    static std::set<T*> collection; \
    static ComponentAllocator<T, N> componentAllocator; \
    static void destroy(T* ptr);\
    template<typename... Args> \
    static auto createComponent(Args&& ... params){\
        auto ptr = componentAllocator.allocate(std::forward<Args>(params)...); \
        collection.insert(ptr); \
        return std::shared_ptr<T>(ptr, &destroy); \
    } \
    friend ComponentAllocator<T, N>;


#define COMPONENT_DEFINATION(P, T, N) \
    const std::string T::name = #T; \
    const std::size_t T::componentId = std::hash<std::string>()(#T); \
    bool T::isType(const std::size_t& typeId) const { \
        if ( typeId == T::componentId ) \
        return true; \
        return P::isType( typeId ); \
    }\
    ComponentAllocator<T, N> T::componentAllocator = ComponentAllocator<T, N>(); \
    \
    void T::destroy(T* ptr) { \
        collection.erase(ptr); \
        componentAllocator.deallocate(ptr); \
    } \
    std::set<T*> T::collection = std::set<T*>(); \

#define COMPONENT_EDITABLE_DEC()\
    static std::function<void(GameObject* go, void* arr)> addToGameObject; \
    static bool isComponentReg; \

#define COMPONENT_EDITABLE_DEF_BEGIN(T)\
    std::function<void(GameObject*, void*)> T::addToGameObject = [](GameObject* go, void* args)

#define COMPONENT_EDITABLE_DEF_END(T)\
    bool T::isComponentReg = registerComponent<T>();\

namespace wlEngine {
    class GameObject;
    struct Component {
    public:
        static std::map<std::string, std::function<void(GameObject*, void*)>> componentFactoryList;
        Component(GameObject* go);
        GameObject* gameObject = nullptr;
        std::set<GameObject*>* gameObjects = nullptr;

        static const std::size_t componentId;
        virtual bool isType(const std::size_t& typeId) const;

        virtual void destruct(GameObject* go){};
        virtual ~Component(){};
        template<class T>
            static bool registerComponent();
    };

    template<class T>
        bool Component::registerComponent() {
            componentFactoryList[T::name] = T::addToGameObject;
            return true;
        }
}



