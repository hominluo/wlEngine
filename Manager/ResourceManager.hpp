#pragma once
#include <map>
#include <string>
#include "../Component/Struct/Texture.hpp"

namespace wlEngine {
    using TextureMap = std::map<std::string, Texture>;
    class ResourceManager {
    public:
        static void init();
        static ResourceManager* get() {return resourceManager;};
        ~ResourceManager();

        Texture* getTexture(const std::string& path);
        const TextureMap& getTextures();
    private:
        Texture* loadTexture(const std::string& path);
        static ResourceManager* resourceManager;
        ResourceManager();

        TextureMap textures;
    };
}
