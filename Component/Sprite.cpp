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
    COMPONENT_EDITABLE_DEF_BEGIN(Sprite){
        std::string path(*static_cast<std::string*>(args[0]));
        std::string shader(*static_cast<std::string*>(args[1]));
        go->addComponent<Sprite>(path, shader);
    };
	COMPONENT_EDITABLE_DEF_END(Sprite);

    Sprite::~Sprite(){};

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
