#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <glad/glad.h>
#include <stb_image.hpp>

#include "Texture.hpp"
#include "../Camera.hpp"
#include "../../EngineManager.hpp"

namespace wlEngine {
	COMPONENT_DEFINATION(Component, Texture, 100);

    Texture::Texture(GameObject* go): Component(go), mTexture(0), mShader(), mWidth(0), mHeight(0), VAO(0), VBO(0), EBO(0) {
        
    }

    Texture::~Texture() {
        free();
    }

    bool Texture::loadFromFile(std::string path) {
        free();

		int nrChannel;
        unsigned char* imageData = stbi_load(path.c_str(), &mWidth, &mHeight, &nrChannel, 0);
		if (!imageData) return false;
        //float mNormalizationPara = mWidth > mHeight ? mWidth : mHeight; // vertex data has to aligned with opengl standard!
		vertices[0] = mWidth;
		vertices[1] = mHeight;
		vertices[5] = mWidth;
		vertices[16] = mHeight;
		unsigned int glColorChannel = nrChannel == 4 ? GL_RGBA : GL_RGB;

		unsigned int indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

        glGenTextures(1, &mTexture);
        glBindTexture(GL_TEXTURE_2D, mTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, glColorChannel, GL_UNSIGNED_BYTE, imageData);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(imageData);
        return true;
    }

    void Texture::loadShader(const char* vertexPath, const char* fragmentPath) {
        mShader = Shader(vertexPath, fragmentPath);
    }

    void Texture::free() {
        glDeleteTextures(1, &mTexture);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		glDeleteBuffers(1, &VAO);
    }
}
