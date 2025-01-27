#pragma once
#include <unordered_set>

#define SYSTEM_DECLARATION(SystemName) \
    public: \
        static SystemName* get(); \
        static SystemName* init(); \
        void update() override; \
    private: \
        static SystemName* system; \
        SystemName(); \

#define SYSTEM_DEFINATION(SystemName) \
    SystemName* SystemName::system = nullptr; \
    SystemName* SystemName::get() { \
        return system; \
    } \
    SystemName* SystemName::init() { \
        system = new SystemName(); \
        System::registerSystem(system); \
        return system; \
    } 
namespace wlEngine {
    class System {
    public:
        virtual void update() {};
        static std::unordered_set<System*> collection;

    protected:
        static void registerSystem(System*); //register the system to collection

    };
}
