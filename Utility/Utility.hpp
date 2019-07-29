#pragma once
#include <string>
#include <sstream>
#include <json.hpp>
#ifdef _WIN32
#include <Windows.h>
#endif
namespace wlEngine {
    namespace Utility {
		using Unicode = wchar_t;
		using Json = nlohmann::json;
        template<typename T>
        std::string toPointerString(T* ptr){
            std::ostringstream oss;
            oss << ptr;
            return oss.str();
        }

		Json* findComponentWithName(Json& goJson, const std::string& name);

#ifdef _WIN32
		std::vector<Unicode> convertStringToUnicodeSet(const std::string& text);
		/* Example */
		//auto unicodeVec = Utility::convertStringToUnicodeSet(u8"我");
#endif
	}
}
