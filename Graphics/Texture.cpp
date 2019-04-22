#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <glad/glad.h>
#include <stb_image.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture.hpp"
#include "../EngineManager.hpp"
#include "../Graphics/GraphicsManager.hpp"

namespace wlEngine {
    Texture::Texture(): mTexture(0), mWidth(0), mHeight(0), VBO(0), VAO(0), EBO(0), mShader() {

    }

    Texture::~Texture() {
        free();
    }

    void Texture::render(int x, int y, int z) {
		int windowHeight = GraphicsManager::getGraphicsManager()->getWindowHeight();
		int windowWidht = GraphicsManager::getGraphicsManager()->getWindowWidth();
		auto camera = EngineManager::getwlEngine()->getCurrentScene()->getCamera();
		auto cameraPos = camera->getPosition();
		mShader.use();
		
		glBindTexture(GL_TEXTURE_2D, mTexture);
		
		glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);
		
		model = glm::translate(model, { x,y,z });
		view = glm::lookAt(glm::vec3(cameraPos.x, cameraPos.y, 4000.0f), glm::vec3(cameraPos.x, cameraPos.y, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		proj =  glm::ortho(0.0f, (float)windowWidht, 0.0f, (float)windowHeight, -0.1f, 10000.0f);
		//proj = glm::perspective(glm::radians(45.0f), (float)windowWidht / windowHeight, 0.1f, 100000.0f);
		mShader.setMat4("model", model);
		mShader.setMat4("view", view);
		mShader.setMat4("projection", proj);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    bool Texture::loadFromFile(std::string path) {
        free();

		int nrChannel;
        unsigned char* imageData = stbi_load(path.c_str(), &mWidth, &mHeight, &nrChannel, 0);
		if (!imageData) return false;
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
