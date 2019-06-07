#pragma once
#include <functional>
#include <memory>
#include <string>
#include <set>
#include <iostream>
#include <unordered_set>

#include "Memory.hpp"

#define COMPONENT_DECLARATION(parentClass, TypeClass, N) \
static const std::size_t componentId; \
virtual bool isType(const std::size_t& typeId) const override; \
static std::set<TypeClass*> collection; \
static ComponentAllocator<TypeClass, N> componentAllocator; \
static void destroy(TypeClass* ptr);\
template<typename... Args> \
static auto createComponent(Args&& ... params){\
    auto ptr = componentAllocator.allocate(std::forward<Args>(params)...); \
    collection.insert(ptr); \
    return std::shared_ptr<TypeClass>(ptr, &destroy); \
} \
friend ComponentAllocator<TypeClass, N>;

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
collection.erase(ptr); \
componentAllocator.deallocate(ptr); \
} \
std::set<TypeClass*> TypeClass::collection = std::set<TypeClass*>(); \

#define VIRTUAL_COMPONENT_DECLARATION(TypeName) \
        static const std::size_t componentId; \
        virtual bool isType(const std::size_t& typeId) const override; \
        static std::set<TypeName*> collection; \

#define VIRTUAL_COMPONENT_DEFINATION(ParentName, TypeName) \
const std::size_t TypeName::componentId = std::hash<std::string>()(#TypeName); \
bool TypeName::isType(const std::size_t& typeId) const { \
if ( typeId == TypeName::componentId ) \
return true; \
return ParentName::isType( typeId ); \
}\
std::set<TypeName*> TypeName::collection = std::set<TypeName*>(); 

#define DERIVED_VIRTUAL_COMPONENT_DECLARATION(ParentName, TypeName, N) \
static const std::size_t componentId; \
virtual bool isType(const std::size_t& typeId) const override; \
static ComponentAllocator<TypeName, N> componentAllocator; \
static void destroy(TypeName* ptr);\
template<typename... Args> \
static auto createComponent(Args&& ... params){\
    auto ptr = componentAllocator.allocate(std::forward<Args>(params)...); \
    ParentName::collection.insert(ptr); \
    return std::shared_ptr<TypeName>(ptr, &destroy); \
} \

#define DERIVED_VIRTUAL_COMPONENT_DEFINATION(ParentName, TypeName, N) \
const std::size_t TypeName::componentId = std::hash<std::string>()(#TypeName); \
bool TypeName::isType(const std::size_t& typeId) const { \
if ( typeId == TypeName::componentId ) \
return true; \
return ParentName::isType( typeId ); \
}\
ComponentAllocator<TypeName, N> TypeName::componentAllocator = ComponentAllocator<TypeName, N>(); \
\
void TypeName::destroy(TypeName* ptr) { \
ParentName::collection.erase(ptr); \
componentAllocator.deallocate(ptr); \
} \


#define STATIC_DECLARATION(P, T) \
static const std::size_t componentId; \
virtual bool isType(const std::size_t& typeId) const override; \
static T* component; \
static void destroy(T* ptr);\
template<typename... Args> \
static auto createComponent(Args&& ... params){\
    component = new T(std::forward(params)); \
    return std::shared_ptr<T>(ptr, &destroy); \
} \

//TODO: implement static component allocation
namespace wlEngine {
    class GameObject;
    struct Component {
    public:
        Component(GameObject* go): gameObject(go) {};
        GameObject* gameObject;

        static const std::size_t componentId;
        virtual bool isType(const std::size_t& typeId) const;

        virtual ~Component(){};
    };
}



