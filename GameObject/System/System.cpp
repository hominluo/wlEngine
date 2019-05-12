#include "System.hpp"

namespace  wlEngine {
    std::set<System*> System::collection = std::set<System*>();

    void System::registerSystem(System* system) {
        collection.insert(system);
    }
}
