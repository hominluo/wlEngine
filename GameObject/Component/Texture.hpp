#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <SDL.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Component.hpp"
#include "../../Graphics/Shader.hpp"

namespace wlEngine {
    /* class Texture
     * @description: use initialized GraphicsManager to draw picture on windowRenderer
     */
	class GameObject;
    struct Texture : Component {
	public:
        COMPONENT_DECLARATION(Component, Texture, 100);
        Texture(GameObject*);
        ~Texture();

        /* load image from path */
        bool loadFromFile(std::string path);

        void free();

        void loadShader(const char* vertexShaderPath = nullptr, const char* fragmentShaderPath = nullptr);

        int getWidth() { return mWidth; };
        int getHeight() { return mHeight; };
        const Shader* getShader() {return &mShader;};

    public:
        unsigned int mTexture;
        Shader mShader;

        int mWidth;
        int mHeight;
        float mNormalizationPara;

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
    };
}
#endif
