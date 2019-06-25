#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <SDL.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Component.hpp"
#include "Struct/Clip.hpp"
#include "../../Graphics/Shader.hpp"

namespace wlEngine {
    /* class Texture
     * @description: use initialized GraphicsManager to draw picture on windowRenderer
     */
	class GameObject;
    struct Sprite : Component {
	public:
        COMPONENT_DECLARATION(Component, Sprite, 100);
        Sprite(GameObject*, const std::string& path);
        ~Sprite();

        /* load image from path */
        bool loadFromFile(const std::string& path);

        void free();

        void useShader(const std::string& name);

        int getWidth() { return mWidth; };
        int getHeight() { return mHeight; };
        void clip(Rect*, bool subData=true);
        Shader* getShader() {return mShader;};

    private:
        unsigned int mTexture;
        Shader* mShader;

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

        friend class RenderSystem;
    };
}
#endif
