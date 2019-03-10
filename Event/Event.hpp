#ifndef EVENT_H
#define EVENT_H
#include <SDL.h>
#include <string>
#include <functional>

namespace wlEngine {
    using EngineEvent = SDL_Event;
    using EventHandler = std::function<void(SDL_Event&)>;


    class Event {
    public:
        struct Hasher {
            size_t operator()(const Event& e) const {
                return std::hash<std::string>()(e.id);
            }
        };

        Event(EventHandler, void* instancePtr, std::string callbackStr);

        bool operator==(const Event& other) const;

        void operator()(SDL_Event&) const;
    private:
        EventHandler handler;
        std::string id;
    };

    #define Create_Event(instance, callback) \
    wlEngine::Event(std::bind(callback, instance, std::placeholders::_1), instance, #callback)
}
#endif
