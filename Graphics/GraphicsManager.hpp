#ifndef GRAPHICS2D_H
#define GRAPHICS2D_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
/* GraphicsManager class
 *
 * @description: contains wrapper functions for 2d rendering in SDL2
 * this class will initialize and configure SDL2 parameters for classes
 * like Texture
 */
namespace wlEngine {
    class GraphicsManager {
    public:
        GraphicsManager();
        ~GraphicsManager();

        static void initialize(const std::string& winTitle, int w, int h);
        static GraphicsManager* getGraphicsManager();
        
        SDL_Renderer* getRenderer();
    private:
        static GraphicsManager* graphicsManager;

        SDL_Renderer* mWindowRenderer;
        SDL_Window* mWindow;
    };
}

#endif 
