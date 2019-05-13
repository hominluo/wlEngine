#pragma once
#include <set>

namespace wlEngine {
    class System {
    public:
		virtual void update() {};
		static std::set<System*> collection;

	protected:
        static void registerSystem(System*); //register the system to collection
        
   };
}
