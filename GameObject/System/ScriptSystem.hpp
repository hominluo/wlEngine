#pragma once
#include "System.hpp"
namespace wlEngine {
    class ScriptSystem : public System {
        ScriptSystem();
        void update() override;
    };
}
