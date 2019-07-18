#include "Utility.hpp"
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
    }
}
