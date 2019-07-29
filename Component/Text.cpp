#include "Text.hpp"
#include "../Manager/ResourceManager.hpp"
#include <glm/gtc/matrix_transform.hpp>
namespace wlEngine {
	COMPONENT_DEFINATION(Component, Text, 32);
	Text::Text(Entity* entity) : Component(entity){
		shader = Shader::collection["text_shader"];
		
	}

	void Text::loadFromFile(const std::string& fileName) {

	}

	void Text::loadText(const std::wstring& textStr) {
        auto resourceManager = ResourceManager::get();
        int advance = 0;
		int offsetY = 0;
        for (const wchar_t& character : textStr) {
            if (character == L'\n') {
				offsetY -= 40; // note: 40 is a magic number! becuase we use FT_Set_Pixel_Sizes(face, 32, 32); in ResourceManager! Be aware!
				advance = 0;
                continue;
            }
            auto textTexture = resourceManager->getTextTexture(character);
      
			text.emplace_back(textTexture, advance, offsetY);
			advance += resourceManager->getFreeTypeFace()->glyph->advance.x >> 6; // The advance vector is expressed in 1/64th of pixels
        }
	}

	void Text::setSettings(const TextSettings& settings) {
		this->settings = settings;
	}

    glm::mat4 Text::Character::getTextTransform() {
        return glm::translate(glm::mat4(1.0), {x,offsetY,0});
    }
    Text::Character::Character(Texture* t, const int& x, const int& offsetY) : texture(t), x(x), offsetY(offsetY){}
}
