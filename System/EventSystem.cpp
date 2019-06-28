#include "EventSystem.hpp"
#include "UISystem.hpp"
namespace wlEngine {
    SYSTEM_DEFINATION(EventSystem);

    EventSystem::EventSystem() {

        registerSystem(this);
    }   

    void EventSystem::update() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            UISystem::get()->eventUpdate(event);
        }
    }
}
