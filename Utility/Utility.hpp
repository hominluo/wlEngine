#pragma once
#include <string>
#include <sstream>
#include <json.hpp>
namespace wlEngine {
    namespace Utility {
		using Json = nlohmann::json;
        template<typename T>
            std::string toPointerString(T* ptr){
                std::ostringstream oss;
                oss << ptr;
                return oss.str();
            }

			Json* findComponentWithName(Json& goJson, const std::string& name);
    }
}
