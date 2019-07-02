#pragma once
#define GL_GLEXT_PROTOTYPES
#include <SDL.h>
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <stb_image.hpp>

#include "System.hpp"

//NOTE: The G-Syn is limiting the frame rate to 60 I think!
class b2World;
namespace wlEngine {
    struct Sprite;
    struct Model;
    class GameEditor;
    class RenderSystem : public System {
    public:
        static RenderSystem* get();
        static void init();
        ~RenderSystem();

        void render();
        void UIRender();
        void inputHandler(SDL_Event& event);
        
        void update() override;

        void setViewPort(int x, int y, int width, int height);

        SDL_GLContext* getSDL_GLContext() {return &glContext;};
        SDL_Window* getSDL_Window() {return window;};
    private:
        static RenderSystem* renderSystem;
        int windowHeight = 720;
        int windowWidth = 1280;
        int sceneHeight = 720;
        int sceneWidth = 1280;
        const int topMenuHeight = 20;

        RenderSystem();

        void SDLInit();
        void ImGuiInit();

        void renderGame();
        void render(Sprite*);
        void render(Model*);

        SDL_GLContext glContext;
        SDL_Window* window;
        GameEditor* gameEditor;

        glm::mat4 projection;

        int windowResizeCallback(void* data, SDL_Event* event);
        static int windowResizeCallbackWrapper(void* data, SDL_Event* event);

        friend class PhysicsDebugDraw;
        friend class GameEditor;
    };
}
