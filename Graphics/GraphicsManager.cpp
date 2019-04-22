

#include <iostream>

#include "GraphicsManager.hpp"
namespace wlEngine {
    GraphicsManager* GraphicsManager::graphicsManager = nullptr;

    GraphicsManager::GraphicsManager() {
        if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
            std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
            exit(-1);
        }
        
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
        SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
        stbi_set_flip_vertically_on_load(true);
        window = SDL_CreateWindow("OpenGL Test", 0, 0, winWidth, winHeight, SDL_WINDOW_OPENGL);
        glContext = SDL_GL_CreateContext(window);
        gladLoadGLLoader(SDL_GL_GetProcAddress);
        glEnable(GL_DEPTH_TEST);

    }

    GraphicsManager::~GraphicsManager() {}

    GraphicsManager* GraphicsManager::initialize(const std::string& winTitle, int w, int h) {
        GraphicsManager::graphicsManager = new GraphicsManager();

        return graphicsManager;
    }

    GraphicsManager* GraphicsManager::getGraphicsManager() {
        return graphicsManager;
    }

    int GraphicsManager::getWindowWidth() {
        return winWidth;
    }

    int GraphicsManager::getWindowHeight() {
        return winHeight;
    }

    void GraphicsManager::beginRenderScene(){
        //glViewport(0, 0, winWidth, winHeight);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
    }

    void GraphicsManager::endRenderScene(){
        SDL_GL_SwapWindow(window);
    }
}
