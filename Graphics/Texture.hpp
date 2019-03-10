#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

namespace wlEngine {
    /* class Texture
     * @description: use initialized GraphicsManager to draw picture on windowRenderer
     */
    class Texture {
    public:
        Texture();

        ~Texture();

        /* load image from path */
        bool loadFromFile(std::string path);

        void free();

        /* render the texture to screen
         * x, y is the position in the windows space
         * clip is used for cliping from the texture image */
        void render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

        int getWidth();
        int getHeight();

        //SDL_Texture* getTexture() {return mTexture;}
        
        operator SDL_Texture* () const {return mTexture;}
    private:
        SDL_Texture* mTexture;

        int mWidth;
        int mHeight;
    };
}
#endif
