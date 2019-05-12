#pragma once
#include <set>

namespace wlEngine {
    class System {
    public:
		virtual void update() {};
        static void registerSystem(System*);
        static std::set<System*> collection;
   };
}
