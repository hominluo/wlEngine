#pragma once
#define GL_GLEXT_PROTOTYPES
#include <SDL.h>
#include <string>
#include <glad/glad.h>
#include <stb_image.hpp>

#include "System.hpp"

class b2World;
namespace wlEngine {
    struct Texture;
    class RenderSystem : public System {
    public:
        static RenderSystem* get();
        static void init();

        void render();
        void render(Texture*);
        
        void update() override;
    private:
        static RenderSystem* renderSystem;
        int windowHeight = 720;
        int windowWidth = 1280;

        RenderSystem();

        void beginRenderScene();
        void endRenderScene();

        SDL_GLContext glContext;
        SDL_Window* window;
    };

}
