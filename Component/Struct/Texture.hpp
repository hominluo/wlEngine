#pragma once
#include <glad/glad.h>
#include <stb_image.hpp>
#include "../../Graphics/Shader.hpp"
#include "Clip.hpp"

namespace wlEngine {
    struct Texture {
        unsigned int mTexture;

        int mWidth;
        int mHeight;

        float normalizationPara;

		//opengl
		GLuint VAO;
		GLuint VBO;
		GLuint EBO;
        
        float vertices[20] = {
            0.0f,  0.0f, 0.0f,  1.0f, 1.0f,   // top right
            0.0f,  0.0f, 0.0f,  1.0f, 0.0f,   // bottom right
            0.0f,  0.0f, 0.0f,  0.0f, 0.0f,   // bottom left
            0.0f,  0.0f, 0.0f,  0.0f, 1.0f    // top left 
        };

        void loadFromFile(const std::string& path);
        void clip(Rect*, bool subData=true);
        void free();
    };
}
