#include "Component.hpp"

namespace wlEngine {
    const std::size_t Component::componentId = std::hash<std::string>()("Component");
    bool Component::isType(const std::size_t& typeId) const {
        return Component::componentId == typeId;
    }
}

