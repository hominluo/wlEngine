#pragma once
#include <functional>
#include <memory>
#include <string>
#include <set>
#include <iostream>
#include <unordered_set>

#include "Memory.hpp"

#define COMPONENT_DECLARATION(P, T, N) \
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

namespace wlEngine {
    class GameObject;
    struct Component {
    public:
        Component(GameObject* go);
        GameObject* gameObject = nullptr;
        std::set<GameObject*>* gameObjects = nullptr;

        static const std::size_t componentId;
        virtual bool isType(const std::size_t& typeId) const;

        virtual void destruct(GameObject* go){};
        virtual ~Component(){};
    };
}



