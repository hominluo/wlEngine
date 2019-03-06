#include "EventManager.hpp"
#include <algorithm>

namespace wlEngine {
    EventManager* EventManager::eventManager = nullptr;

    EventManager::EventManager(){};

    void EventManager::pollEvent() {
        while (SDL_PollEvent(&event)) {
            for (auto iter = handlers.begin(); iter != handlers.end(); iter++) {
                (*iter)(event);
            }
        }
    }

    void EventManager::registerEvent(Event e) {
        handlers.insert(e);
    }

    void EventManager::unregisterEvent(Event e) {
        handlers.erase(e);
    }

    EventManager* EventManager::initialize() {
        eventManager = new EventManager();

        return eventManager;
    }

    EventManager* EventManager::getEventManager() {
        if (EventManager::eventManager) return EventManager::eventManager;
#ifdef DEBUG
        assert(0)
#endif
        return nullptr;
    }
}
