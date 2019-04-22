#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "Shader.hpp"

namespace wlEngine {
    /* class Texture
     * @description: use initialized GraphicsManager to draw picture on windowRenderer
     */
    class Texture {
    public:
        Texture();

        ~Texture();

        /* load image from path */
        bool loadFromFile(std::string path);

        void free();

        void render(int x, int y, int z);
        void loadShader(const char* vertexShaderPath = nullptr, const char* fragmentShaderPath = nullptr);

        int getWidth() { return mWidth; };
        int getHeight() { return mHeight; };
        const Shader* getShader() {return &mShader;};

    private:
        unsigned int mTexture;
        Shader mShader;

        int mWidth;
        int mHeight;

		//opengl
		GLuint VAO;
		GLuint VBO;
		GLuint EBO;
		float vertices[20] = {
			// positions        // texture coords
			0.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
			0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
			0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom left
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f  // top left
		};
    };
}
#endif
