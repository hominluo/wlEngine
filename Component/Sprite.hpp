#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "../GameObject/GameObject.hpp"

#include <SDL.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Component.hpp"
#include "Struct/Clip.hpp"
#include "../Graphics/Shader.hpp"
#include "Struct/Texture.hpp"
namespace wlEngine {
    /* class Texture
     * @description: use initialized GraphicsManager to draw picture on windowRenderer
     */
	class GameObject;
    struct Sprite : Component {
	public:
        COMPONENT_DECLARATION(Component, Sprite, 100);
        COMPONENT_EDITABLE_DEC();

        Sprite(GameObject*, Texture*);
        Sprite(GameObject*, const std::string& path);
        Sprite(GameObject*, const std::string& path, const std::string& shader);
        ~Sprite();

        void useShader(const std::string&);
        void loadTexture(const std::string& path);

        Texture* texture;
    private:
        Shader* shader;

        friend class RenderSystem;
        friend class GameEditor;
    };
}
#endif
