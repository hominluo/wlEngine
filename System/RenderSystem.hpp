#pragma once
#define GL_GLEXT_PROTOTYPES
#include <SDL.h>
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <stb_image.hpp>

#include "System.hpp"
#include "../Settings.hpp"
#include "../Component/Camera2D.hpp"
//NOTE: The G-Syn is limiting the frame rate to 60!
class b2World;
namespace wlEngine {
    struct Sprite;
    struct Model;
    class GameEditor;
    class Camera3D;
    class RenderSystem : public System {
    public:
        static RenderSystem* get();
        static void init();
        ~RenderSystem();

        void render();
        
        void inputHandler(SDL_Event& event);
        
        void update() override;

        void setViewPort(int x, int y, int width, int height);

        SDL_GLContext* getSDL_GLContext() {return &glContext;};
        SDL_Window* getSDL_Window() {return window;};
        glm::vec2 getWindowSize() {return {windowWidth, windowHeight};};
        glm::vec2 getSceneSize() {return {sceneWidth, sceneHeight};};
    private:
#if SETTINGS_ENGINEMODE
        unsigned int sceneTexture;
        unsigned int sceneFramebuffer;
        unsigned int depthAndStencilTexture;
		void renderGameEditor();
#endif

        static RenderSystem* renderSystem;
		int windowHeight = 768;
        int windowWidth = 1440;
        int sceneHeight = 360;
        int sceneWidth = 640;
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
        Camera2D* camera2D = nullptr;
        Camera3D* camera3D = nullptr; //under development

        glm::mat4 projection;

        int windowResizeCallback(void* data, SDL_Event* event);
        static int windowResizeCallbackWrapper(void* data, SDL_Event* event);

        friend class PhysicsDebugDraw;
        friend class GameEditor;
        friend class EngineManager;
    };
}
