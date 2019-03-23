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
        ~GraphicsManager();

        /* w: window width
         * h: window height*/
        static GraphicsManager* initialize(const std::string& winTitle, int w, int h);
        static GraphicsManager* getGraphicsManager();
        
        SDL_Renderer* createRenderer();
        void destroyRenderer();
        SDL_Renderer* getRenderer();
        int getWindowWidth();
        int getWindowHeight();
        

    private:
        GraphicsManager();

        static GraphicsManager* graphicsManager;

        SDL_Renderer* mRenderer;
        SDL_Window* mWindow;
    };
}

#endif 
