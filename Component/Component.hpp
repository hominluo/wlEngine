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
    public:\
    static const std::size_t componentId; \
    virtual bool isType(const std::size_t& typeId) const override; \
    static std::set<T*> collection; \
    static FixedArrayAllocator<T, N> fixedArrayAllocator; \
    static void destroy(T* ptr);\
    template<typename... Args> \
    static auto createComponent(Entity* go, Args&& ... params){\
        auto ptr = fixedArrayAllocator.allocate(go, std::forward<Args>(params)...); \
        collection.insert(ptr); \
        return std::shared_ptr<T>(ptr, &destroy); \
    } \
    virtual std::size_t getId() override;\
    private:\
    friend FixedArrayAllocator<T, N>;


#define COMPONENT_DEFINATION(P, T, N) \
    const std::size_t T::componentId = std::hash<std::string>()(#T);\
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
public:\
    static std::function<void(Entity* go, void** arr)> addToEntity; \
    static bool isComponentReg; \
private:\

#define COMPONENT_EDITABLE_DEF(T)\
    std::function<void(Entity*, void**)> T::addToEntity = [](Entity* go, void** args) { \
        go->addComponent<T>(args);\
    };\
    bool T::isComponentReg = registerComponent<T>();

namespace wlEngine {
    class Entity;
    struct Component {
    public:
        static std::size_t genComponentId(const std::string&);
		static std::map<std::size_t, std::string>* componentIdToName; // this now is only used for Script, leave it here for extensibility
		static std::map<std::size_t, std::string>* getComponentIdToName();
        static std::map<std::size_t, std::function<void(Entity*, void**)>>* componentFactoryList;
		static std::map<std::size_t, std::function<void(Entity*, void**)>>* getComponentFactoryList();
        Component(Entity* go);
        Entity* entity = nullptr;
        std::set<Entity*>* entities = nullptr;

        static const std::size_t componentId;
        virtual bool isType(const std::size_t& typeId) const;

        virtual void destruct(Entity* go){};
        virtual std::size_t getId();
        virtual ~Component(){};
        template<class T>
            static bool registerComponent();
    };

    template<class T>
        bool Component::registerComponent() {
            (*getComponentFactoryList())[T::componentId] = T::addToEntity;
            return true;
        }
}



