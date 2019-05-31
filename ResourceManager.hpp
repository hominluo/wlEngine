#pragma once
#include <map>
#include <string>

namespace wlEngine {
    class ResourceManager {
    public:
        static void init();
        static ResourceManager* get() {return resourceManager;};
        unsigned char* getImage(const std::string& path, int& width, int& height, int& nrComponents);
        ~ResourceManager();

    private:
        static ResourceManager* resourceManager;
        ResourceManager();
        std::map<std::string, unsigned char*> images;
    };
}
