#include "ResourceManager.hpp"
#include <stb_image.hpp>
namespace wlEngine {
    ResourceManager* ResourceManager::resourceManager = nullptr;
    void ResourceManager::init() {
        resourceManager = new ResourceManager();
    }

    unsigned char* ResourceManager::getImage(const std::string& path, int& width, int& height, int& nrComponents) {
        auto iter = images.find(path);
        if (iter != images.end()) {
            return iter->second;
        }
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
        images[path] = data;
        return data;
    }
}
