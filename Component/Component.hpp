#pragma once
#include <functional>
#include <memory>
#include <string>
#include <set>
#include <iostream>
#include <unordered_set>
#include <map>

#include "../Memory/FixedArrayAllocator.hpp"

#define COMPONENT_DECLARATION(P, T, N) \
    static const std::size_t componentId; \
    virtual bool isType(const std::size_t& typeId) const override; \
    static std::set<T*> collection; \
    static FixedArrayAllocator<T, N> fixedArrayAllocator; \
    static void destroy(T* ptr);\
    template<typename... Args> \
    static auto createComponent(Args&& ... params){\
        auto ptr = fixedArrayAllocator.allocate(std::forward<Args>(params)...); \
        collection.insert(ptr); \
        return std::shared_ptr<T>(ptr, &destroy); \
    } \
    virtual std::size_t getId() override;\
    friend FixedArrayAllocator<T, N>;


#define COMPONENT_DEFINATION(P, T, N) \
    const std::size_t T::componentId = std::hash<std::string>()(#T); \
    bool T::isType(const std::size_t& typeId) const { \
        if ( typeId == T::componentId ) \
        return true; \
        return P::isType( typeId ); \
    }\
    FixedArrayAllocator<T, N> T::fixedArrayAllocator = FixedArrayAllocator<T, N>(); \
    \
    void T::destroy(T* ptr) { \
        collection.erase(ptr); \
        fixedArrayAllocator.deallocate(ptr); \
    } \
    std::size_t T::getId() { \
        return componentId;\
    }\
    std::set<T*> T::collection = std::set<T*>(); \

#define COMPONENT_EDITABLE_DEC()\
    static std::function<void(GameObject* go, void** arr)> addToGameObject; \
    static bool isComponentReg; \

#define COMPONENT_EDITABLE_DEF_BEGIN(T)\
    std::function<void(GameObject*, void**)> T::addToGameObject = [](GameObject* go, void** args)

#define COMPONENT_EDITABLE_DEF_END(T)\
    bool T::isComponentReg = registerComponent<T>();\

namespace wlEngine {
    class GameObject;
    struct Component {
    public:
        static std::map<std::size_t, std::function<void(GameObject*, void**)>>* componentFactoryList;
		static std::map<std::size_t, std::function<void(GameObject*, void**)>>* getComponentFactoryList();
        Component(GameObject* go);
        GameObject* gameObject = nullptr;
        std::set<GameObject*>* gameObjects = nullptr;

        static const std::size_t componentId;
        virtual bool isType(const std::size_t& typeId) const;

        virtual void destruct(GameObject* go){};
        virtual std::size_t getId();
        virtual ~Component(){};
        template<class T>
            static bool registerComponent();
    };

    template<class T>
        bool Component::registerComponent() {
            (*getComponentFactoryList())[T::componentId] = T::addToGameObject;
            return true;
        }
}



