#include "ResourceManager.hpp"
#include <stb_image.hpp>
namespace wlEngine {
    ResourceManager* ResourceManager::resourceManager = nullptr;
    void ResourceManager::init() {
        resourceManager = new ResourceManager();
    }
    
}
