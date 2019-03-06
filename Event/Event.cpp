#include "Event.hpp"
#include <sstream>

namespace wlEngine {
    Event::Event(EventHandler handler, void* instancePtr, std::string callbackStr): handler(handler){
        std::ostringstream out;
        out << instancePtr << "+" << callbackStr;
        id = out.str();
    };

    bool Event::operator==(const Event& other) const {
        return id == other.id;
    }

    void Event::operator()(SDL_Event& e) const {
        handler(e);
    }

}
