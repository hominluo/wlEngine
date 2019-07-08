#include "ResourceManager.hpp"

#include <stb_image.hpp>
#include <algorithm>
#include <locale.h>
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <stb_image.hpp>

namespace wlEngine {
    ResourceManager* ResourceManager::resourceManager = nullptr;

    ResourceManager::ResourceManager() {
    }
    void ResourceManager::init() {
        resourceManager = new ResourceManager();
        setlocale (LC_ALL, "");
    }

    Texture* ResourceManager::loadTexture(const std::string& path) {
        return textures[path].loadFromFile(path);
    }

    Texture* ResourceManager::getTexture(const std::string& path) {
		auto t = textures.find(path);
        if (t == textures.end()) {
            return loadTexture(path);
        }
        return &t->second;
    }

    const TextureMap& ResourceManager::getTextures(){
        return textures;
    }
}
