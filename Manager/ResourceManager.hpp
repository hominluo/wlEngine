#pragma once
#include <map>
#include <string>
#include "../Graphics/Texture.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H

namespace wlEngine {
    struct TextInfo {
        Texture text;
        FT_Face face;
    };
    using TextureMap = std::map<std::string, Texture>;
	using TextTextureMap = std::map<std::wstring, TextInfo>;
    class ResourceManager {
    public:
        static void init();
        static ResourceManager* get() {return resourceManager;};
		~ResourceManager();

        Texture* getTexture(const std::string& path);
        
        const TextureMap& getTextures();
		/* FreeType *************************************/
		TextInfo* getTextTexture(const wchar_t& wildCharacter, const int& pixelSizeWidth, const int& pixelSizeHeight);
    private:
        static ResourceManager* resourceManager;
        ResourceManager();
		TextureMap textures;
		TextTextureMap textTextures;
		Texture* loadTexture(const std::string& path);

		FT_Library freeTypeLibrary;
		FT_Face face;
    };
}
