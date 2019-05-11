#ifndef GRAPHICS2D_H
#define GRAPHICS2D_H

#define GL_GLEXT_PROTOTYPES

#include <SDL.h>
#include <string>
#include <glad/glad.h>
#include <stb_image.hpp>

/* GraphicsManager class
 *
 * @description: contains wrapper functions for 2d rendering in SDL2
 * this class will initialize and configure SDL2 parameters for classes
 * like Texture
 */
namespace wlEngine {
    class GraphicsManager {
    public:
        ~GraphicsManager();

        static GraphicsManager* initialize(const std::string& winTitle, int w, int h);
        static GraphicsManager* getGraphicsManager();

        int getWindowWidth();
        int getWindowHeight();
        
        void beginRenderScene();
        void endRenderScene();

    private:
        GraphicsManager();

        static GraphicsManager* graphicsManager;
        
        SDL_GLContext glContext;
        SDL_Window* window;

        const int winWidth = 1280;
        const int winHeight = 720;
    };
}

#endif 
