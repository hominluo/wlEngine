#pragma once
#include "Component.hpp"
namespace wlEngine {
    struct Script : public Component {
        COMPONENT_DECLARATION(Component, Script, 100);

        virtual void update() = 0;
    };
}
