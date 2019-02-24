#include <iostream>

#include "GraphicsManager.hpp"

namespace wlEngine {
    GraphicsManager* GraphicsManager::graphicsManager = nullptr;

    GraphicsManager::GraphicsManager() {

    }

    GraphicsManager::~GraphicsManager() {}

    void GraphicsManager::initialize(const std::string& winTitle, int w, int h) {
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

        graphicsManager->mWindow = SDL_CreateWindow(winTitle.c_str(),SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h,SDL_WINDOW_SHOWN);
        if (!graphicsManager->mWindow) {
            std::cerr << "SDL could not initialize window: " << SDL_GetError() << std::endl;
            exit(-1);
        }

        graphicsManager->mWindowRenderer = SDL_CreateRenderer(graphicsManager->mWindow, -1 , SDL_RENDERER_ACCELERATED);
        if (!graphicsManager->mWindowRenderer) {
            std::cerr << "SDL could not initialize window renderer: " << SDL_GetError() << std::endl;
            exit(-1);
        }

        SDL_SetRenderDrawColor(graphicsManager->mWindowRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

        if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) {
            std::cerr << "SDL_image could not initialize: " << SDL_GetError() << std::endl;
            exit(-1);
        }


    }

    GraphicsManager* GraphicsManager::getGraphicsManager() {
#ifdef DEBUG
        assert(graphicsManager != nullptr)
#endif
        return graphicsManager;
    }

    SDL_Renderer* GraphicsManager::getRenderer() {
        return mWindowRenderer;
    }
}
