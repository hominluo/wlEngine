#include "System.hpp"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_sdl.h"
#include "../imgui/imgui_impl_opengl3.h"

#include <SDL.h>

namespace wlEngine {
    class UISystem : System{
        SYSTEM_DECLARATION(UISystem);

    public:
        /**
         * @brief called by RenderSystem for UI rendering
         */
        void render();
        /**
         * @brief callled by EventManager. process the event polled from SDL2
         *
         * @param e the event
         */
        void eventUpdate(SDL_Event& e);

    private:
        SDL_Window* window;
        SDL_GLContext* context;
    };
}
