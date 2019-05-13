#pragma once
#include "Component.hpp"

//TODO: Script should be a shared component
namespace wlEngine {
    struct Script : public Component {
        VIRTUAL_COMPONENT_DECLARATION(Script);

        Script(GameObject* go) : Component(go){};
        virtual void update() = 0;
    };
}
