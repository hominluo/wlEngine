#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include <SDL.h>
#include <unordered_set>

#include "Event.hpp"

//check this for key press event
/*https://stackoverflow.com/questions/1252976/how-to-handle-multiple-keypresses-at-once-with-sdl*/
namespace wlEngine {
    class EventManager {
    public:
        static EventManager* getEventManager();
        static EventManager* initialize();

        void registerEvent(Event e);
        void unregisterEvent(Event e);

        ~EventManager();
        void pollEvent();
    private:
        static EventManager* eventManager;

        SDL_Event event;

        std::unordered_set<Event, Event::Hasher> handlers; //  feel like this is a really stupid design

        EventManager();
    };
}

#endif