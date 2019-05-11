#pragma once
#include <functional>
#include <memory>
#include <string>
#include <set>
#include <iostream>

#include "Memory.hpp"

#define COMPONENT_DEFINATION(ParentClass, TypeClass, N) \
const std::size_t TypeClass::componentId = std::hash<std::string>()(#TypeClass); \
bool TypeClass::isType(const std::size_t& typeId) const { \
if ( typeId == TypeClass::componentId ) \
return true; \
return ParentClass::isType( typeId ); \
}\
ComponentAllocator<TypeClass, N> TypeClass::componentAllocator = ComponentAllocator<TypeClass, N>(); \
\
void TypeClass::destroy(TypeClass* ptr) { \
collection.erase(collection.find(ptr)); \
componentAllocator.deallocate(ptr); \
} \
std::set<TypeClass*> TypeClass::collection = std::set<TypeClass*>(); \

#define COMPONENT_DECLARATION(parentClass, TypeClass, N) \
static const std::size_t componentId; \
virtual bool isType(const std::size_t& typeId) const; \
static std::set<TypeClass*> collection; \
static ComponentAllocator<TypeClass, N> componentAllocator; \
static void destroy(TypeClass* ptr);\
template<typename... Args> \
static auto createComponent(Args&& ... params){\
    auto ptr = componentAllocator.allocate(std::forward<Args>(params)...); \
    collection.insert(ptr); \
    return std::shared_ptr<TypeClass>(std::move(ptr), &destroy); \
} \
friend ComponentAllocator<TypeClass, N>;

namespace wlEngine {
    class GameObject;
    struct Component {
    public:
        Component(GameObject* go):gameObject(go) {};
        GameObject* gameObject;
        
        static const std::size_t componentId;
        virtual bool isType(const std::size_t& typeId) const;
        
        virtual ~Component(){};
    };
}



