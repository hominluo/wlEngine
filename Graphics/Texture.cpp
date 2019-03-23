#include <iostream>

#include "Texture.hpp"
#include "../EngineManager.hpp"

namespace wlEngine {
    Texture::Texture(): mTexture(nullptr), mWidth(0), mHeight(0) {

    }

    Texture::~Texture() {
        free();
    }

    void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
          //Set rendering space and render to screen
          //
        SDL_Rect renderQuad = { x, y , mWidth, mHeight };

        //Set clip rendering dimensions
        if( clip != NULL )
        {
            renderQuad.w = clip->w;
            renderQuad.h = clip->h;
        }

        //Render to screen
        auto engine = EngineManager::getwlEngine();
        SDL_RenderCopyEx( engine->getRenderer(), mTexture, clip, &renderQuad, angle, center, flip);
    }

    bool Texture::loadFromFile(std::string path) {
        free();

        SDL_Texture* newTexture = nullptr;

        SDL_Surface* loadedSurface = IMG_Load(path.c_str());
        if (!loadedSurface) {
            std::cerr << "load from file failed: " << IMG_GetError() << std::endl;
            return false;
        }

        auto engine = EngineManager::getwlEngine();
        newTexture = SDL_CreateTextureFromSurface(engine->getRenderer(), loadedSurface);
        if (!newTexture) {
            std::cerr << "unable to create texture from surface: " << SDL_GetError() << std::endl;
            return false;
        }

        mWidth = loadedSurface->w;
        mHeight = loadedSurface->h;

        SDL_FreeSurface(loadedSurface);

        mTexture = newTexture;
        return true;
    }

    void Texture::free() {
        if (mTexture) SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
    }

    int Texture::getWidth() {
        return mWidth;
    }

    int Texture::getHeight() {
        return mHeight;
    }
}
