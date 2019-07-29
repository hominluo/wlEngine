#pragma once
#include <map>
#include <string>
#include "../Graphics/Texture.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H

namespace wlEngine {
    using TextureMap = std::map<std::string, Texture>;
	using TextTextureMap = std::map<wchar_t, Texture>;
    class ResourceManager {
    public:
        static void init();
        static ResourceManager* get() {return resourceManager;};
		~ResourceManager();

        Texture* getTexture(const std::string& path);
        
        const TextureMap& getTextures();
		FT_Face& getFreeTypeFace();
		/* FreeType *************************************/
		Texture* getTextTexture(const wchar_t& wildCharacter);
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
