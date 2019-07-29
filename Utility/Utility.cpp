#include "Utility.hpp"
#include <vector>
namespace wlEngine {
	namespace Utility {
		Json* Utility::findComponentWithName(Json& j, const std::string& name) {
			for (auto& component : j["components"]) {
				if (component["name"] == name) {
					return &component;
				}
			}
			return nullptr;
		}

#ifdef _WIN32
		std::vector<Unicode> Utility::convertStringToUnicodeSet(const std::string& text) {
			int charNums = MultiByteToWideChar(CP_UTF8, 0, text.c_str(), text.size(), NULL, 0);

			Unicode* cVec = new Unicode[charNums];
			MultiByteToWideChar(CP_UTF8, 0, text.c_str(), text.size(), cVec, charNums);
			std::vector<Unicode> unicodeVec(cVec, cVec + charNums);
			delete[] cVec;
			return unicodeVec;
		}
#endif
	}
}
