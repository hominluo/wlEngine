#pragma once

#include <iostream>
#include <fstream>
#include "Component.hpp"
#include "../Graphics/Texture.hpp"
#include "../Graphics/Shader.hpp"
#include "../Utility/Utility.hpp"

namespace wlEngine {
	struct TextSettings{
		std::string fontPath;
		float pixelSizeWidth;
		float pixelSizeHeight;
	};
	
	class Text : public Component{
		COMPONENT_DECLARATION(Component, Text, 32);
	public:
		Text(Entity* go);

		/* functions ************************************/
		void loadFromFile(const std::string& fileName);
		void loadText(const std::wstring& text);
		void setSettings(const TextSettings& settings);

		/* structs *************************************/
		struct Character {
            Character(Texture* t, const int& x, const int& rows);
			Texture* texture;
			int x;
			int offsetY;
            glm::mat4 getTextTransform();
		};
	private:
        Shader* shader;
		
		TextSettings settings;
		std::vector<Character> text;
		
        friend class RenderSystem;
	};
}
