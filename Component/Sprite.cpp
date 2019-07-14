#define STB_IMAGE_IMPLEMENTATION

#include <iostream>

#include "Animation.hpp"
#include "Sprite.hpp"
#include "../GameObject/Camera.hpp"
#include "../EngineManager.hpp"
#include "../Settings.hpp"

#include "../Manager/ResourceManager.hpp"

namespace wlEngine {
	COMPONENT_DEFINATION(Component, Sprite, 100);
    COMPONENT_EDITABLE_DEF(Sprite);

    Sprite::~Sprite(){};

    Sprite::Sprite(GameObject* go, Texture* t) : Component(go) {
        texture = t;
    }

    Sprite::Sprite(GameObject* go, void** args) : Component(go) {
        std::string path(*static_cast<std::string*>(args[0]));
        std::string shader(*static_cast<std::string*>(args[1]));
        auto resourceManager = ResourceManager::get();
        texture = resourceManager->getTexture(path);
        useShader(shader);
    }

    Sprite::Sprite(GameObject* go, const std::string& path): Component(go) {
        auto resourceManager = ResourceManager::get();
        texture = resourceManager->getTexture(path);

    }
    Sprite::Sprite(GameObject* go, const std::string& path, const std::string& shader) : Sprite(go, path) {
        useShader(shader);
    }

    void Sprite::useShader(const std::string& name){
        shader = Shader::collection[name];
    }
}
