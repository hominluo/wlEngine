#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "../GameObject/GameObject.hpp"

#include <SDL.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Component.hpp"
#include "Struct/Clip.hpp"
#include "../Graphics/Shader.hpp"
#include "../Graphics/Texture.hpp"
namespace wlEngine {
    /* class Texture
     * @description: use initialized GraphicsManager to draw picture on windowRenderer
     */
	class Entity;
    class Sprite : public Component {
        COMPONENT_DECLARATION(Component, Sprite, 100);
        COMPONENT_EDITABLE_DEC();
	public:
        Sprite(Entity*, const std::string& path);
        Sprite(Entity*, const std::string& path, const std::string& shader);
        Sprite(Entity*, void** args);
        ~Sprite();

        void useShader(const std::string&);
        void addTexture(const std::string& name, const std::string& path);
        void removeTexture(const std::string& name);
        std::function<void()> beforeRenderFunc;
        std::function<void()> afterRenderFunc;

        std::map<std::string, Texture*> textures;
        Texture* mainTexture;
        Shader* shader;
    };
}
#endif
