#pragma once
#include "Component.hpp"

#define SCRIPT_DECLARATION(P, T, N) \
static const std::size_t componentId; \
virtual bool isType(const std::size_t& typeId) const override; \
static ComponentAllocator<T, N> componentAllocator; \
static void destroy(T* ptr);\
template<typename... Args> \
static auto createComponent(Args&& ... params){\
    auto ptr = componentAllocator.allocate(std::forward<Args>(params)...); \
    collection.insert(ptr); \
    return std::shared_ptr<T>(ptr, &destroy); \
} \
friend ComponentAllocator<T, N>;

#define SCRIPT_DEFINATION(P, T, N) \
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

namespace wlEngine {
    struct Script : public Component {
        static const std::size_t componentId; 
        virtual bool isType(const std::size_t& typeId) const override; 
        static std::set<Script*> collection; 
        Script(GameObject* go) : Component(go){};
        virtual void update() = 0;
    };
}