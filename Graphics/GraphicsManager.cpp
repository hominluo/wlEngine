#include <iostream>

#include "GraphicsManager.hpp"

namespace wlEngine {
    GraphicsManager* GraphicsManager::graphicsManager = nullptr;

    GraphicsManager::GraphicsManager() {

    }

    GraphicsManager::~GraphicsManager() {}

    GraphicsManager* GraphicsManager::initialize(const std::string& winTitle, int w, int h) {
#ifdef DEBUG
        assert(graphicsManager == nullptr);
#endif
        GraphicsManager::graphicsManager = new GraphicsManager();

        if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
            std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
            exit(-1);
        }

        //Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
            std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
		}

        graphicsManager->mWindow = SDL_CreateWindow(winTitle.c_str(),SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h,SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
        if (!graphicsManager->mWindow) {
            std::cerr << "SDL could not initialize window: " << SDL_GetError() << std::endl;
            exit(-1);
        }

        if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) {
            std::cerr << "SDL_image could not initialize: " << SDL_GetError() << std::endl;
            exit(-1);
        }

        graphicsManager->mRenderer = SDL_CreateRenderer(graphicsManager->mWindow, -1 , SDL_RENDERER_ACCELERATED);
        if (!graphicsManager->mRenderer) {
            std::cerr << "SDL could not initialize window renderer: " << SDL_GetError() << std::endl;
            exit(-1);
        }

        SDL_SetRenderDrawColor(graphicsManager->mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        return graphicsManager;
    }

    GraphicsManager* GraphicsManager::getGraphicsManager() {
#ifdef DEBUG
        assert(graphicsManager != nullptr)
#endif
        return graphicsManager;
    }

    void GraphicsManager::destroyRenderer() {
        SDL_DestroyRenderer(mRenderer);
    }

    SDL_Renderer* GraphicsManager::getRenderer() {
        return mRenderer;
    }

    int GraphicsManager::getWindowWidth() {
        int w,h;
        SDL_GetWindowSize(mWindow, &w, &h);
        return w;
    }

    int GraphicsManager::getWindowHeight() {
        int w,h;
        SDL_GetWindowSize(mWindow, &w, &h);
        return h;
    }

}
