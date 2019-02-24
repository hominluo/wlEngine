#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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
        void render(int x, int y, SDL_Rect* clip = nullptr);

        int getWidth();
        int getHeight();

        SDL_Texture* getTexture() {return mTexture;}
    private:
        SDL_Texture* mTexture;

        int mWidth;
        int mHeight;
    };
}
#endif
