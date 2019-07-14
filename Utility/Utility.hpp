#pragma once
#include <string>
#include <sstream>

namespace wlEngine {
    namespace Utility {
        template<typename T>
            std::string toPointerString(T* ptr){
                std::ostringstream oss;
                oss << ptr;
                return oss.str();
            }
    }
}
