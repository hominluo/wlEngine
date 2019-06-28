#include "System.hpp"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_sdl.h"
#include "../../imgui/imgui_impl_opengl3.h"

#include <SDL.h>

namespace wlEngine {
    class UISystem : System{
        SYSTEM_DECLARATION(UISystem);

    public:
        void render();

    private:
        SDL_Window* window;
        SDL_GLContext* context;
    };
}
