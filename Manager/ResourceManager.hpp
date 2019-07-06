#pragma once
#include <map>
#include <string>

namespace wlEngine {
    class ResourceManager {
    public:
        static void init();
        static ResourceManager* get() {return resourceManager;};
        ~ResourceManager();

    private:
        static ResourceManager* resourceManager;
        ResourceManager();
        std::map<std::string, unsigned char*> images;
    };
}
