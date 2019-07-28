#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>

#include "Component.hpp"
#include "../Graphics/Texture.hpp"
#include "../Graphics/Shader.hpp"


namespace wlEngine {
	class Text : public Component{
		COMPONENT_DECLARATION(Component, Text, 32);
	public:
		Text(GameObject* go) : Component(go), library() {
            shader = Shader::collection["text_shader"]; //text_shader can't do
			FT_Error error = FT_Init_FreeType(&library);
			if (error) {
				std::cerr << "FT Library Init Error\n";
			}
			
			error = FT_New_Face(library, "../wlEngine/etc/fonts/wts11.ttf", 0, &face);
			//FT_Select_Charmap(face, ft_encoding_unicode);
			if (error) {
				std::cerr << "FT Face Init Error\n";
			}

			error = FT_Set_Char_Size(
				face,
				0,
				16 * 64,
				300,
				300);

			FT_UInt glyph_index = FT_Get_Char_Index(face, 'A');
			
			error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);

			error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

			texture.loadFromFTBitmap(face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows);

			FT_Done_Face(face);
			FT_Done_FreeType(library);
		}
	private:
        Shader* shader;
		Texture texture;
		FT_Library library;
		FT_Face face;

        friend class RenderSystem;
	};
}
