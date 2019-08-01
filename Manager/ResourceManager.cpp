#include "ResourceManager.hpp"

#include <stb_image.hpp>
#include <algorithm>
#include <locale.h>
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <stb_image.hpp>

#include "../Utility/Utility.hpp"
namespace wlEngine {
    ResourceManager* ResourceManager::resourceManager = nullptr;
    ResourceManager::~ResourceManager() {
		FT_Done_Face(face);
        FT_Done_FreeType(freeTypeLibrary);
    }

    ResourceManager::ResourceManager() {
		FT_Error error = FT_Init_FreeType(&freeTypeLibrary);
		if (error) {
			std::cerr << "FT Library Init Error\n";
		}

		error = FT_New_Face(freeTypeLibrary, "../wlEngine/etc/fonts/Zpix.ttf", 0, &face);

		if (error) {
			std::cerr << "FT Face Init Error\n";
		}



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

    TextInfo* ResourceManager::getTextTexture(const wchar_t& wideCharacter, const int& pixelSizeWidth, const int& pixelSizeHeight) {
        std::wstring id = std::wstring(1, wideCharacter) + L"_" + std::to_wstring(pixelSizeWidth) + L"_" + std::to_wstring(pixelSizeHeight); // IMPROVE: we can write this as a struct to improve performance
        auto iter = textTextures.find(id);
        if (iter != textTextures.end()) return &textTextures[id];

        FT_UInt glyph_index = FT_Get_Char_Index(face, (FT_ULong)wideCharacter);
		FT_Error error = FT_Set_Pixel_Sizes(
			face,
			pixelSizeWidth, pixelSizeHeight);
        error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
        error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

        auto& t = textTextures[id];
        t.text.loadFromFTBitmap(face->glyph);
        t.face = face;
        return &t;
    }
}
