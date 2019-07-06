#include "ResourceManager.hpp"

#include <stb_image.hpp>
#include <algorithm>
#include <dirent.h>
#include <locale.h>
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <stb_image.hpp>

namespace wlEngine {
    ResourceManager* ResourceManager::resourceManager = nullptr;

    ResourceManager::ResourceManager() {
        visitDirectory("../resource");
    }
    void ResourceManager::init() {
        resourceManager = new ResourceManager();
        setlocale (LC_ALL, "");
    }

    void ResourceManager::loadTexture(const std::string& path) {
        textures[path].loadFromFile(path);
    }

    void ResourceManager::visitDirectory(const std::string& dirname) {
        DIR *dir;
        struct dirent *ent;

        /* Open directory stream */
        dir = opendir (dirname.data());
        if (dir != NULL) {

            /* iterate through all files*/
            while ((ent = readdir (dir)) != NULL) {
                switch (ent->d_type) {
                    case DT_REG:{
                        std::string fileName(ent->d_name);
                        std::size_t dotPos = fileName.find_last_of('.');
                        std::string etx = fileName.substr(dotPos+1, fileName.length());
                        std::transform(etx.begin(), etx.end(), etx.begin(), [](unsigned char c) {return std::tolower(c); });
                        if (etx == "png" || etx == "jpg") loadTexture(dirname +"/"+ fileName);
                        break;
                    }


                    case DT_DIR:
                        if(ent->d_name[0] != '.')
                            visitDirectory(dirname +"/"+ ent->d_name);
                        break;

                    case DT_LNK:
                        printf ("%s@\n", ent->d_name);
                        break;

                    default:
                        printf ("%s*\n", ent->d_name);
                }
            }

            closedir (dir);

        } else {
            std::cerr << "Resource Manager path error\n";
        }
    }

    Texture* ResourceManager::getTexture(const std::string& path) {
        return &textures[path];
    }

    const TextureMap& ResourceManager::getTextures(){
        return textures;
    }
}
