#pragma once
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stb_image.hpp>
#include <functional>

#include "Component.hpp"
#include "../Graphics/Mesh.hpp"

namespace wlEngine {
    struct Model : public Component{
    public:
        COMPONENT_DECLARATION(Component, Model, 50);
        std::vector<Mesh> meshes;
        bool gammaCorrection;
        std::string directory;

        Shader* shader;

        Model(GameObject* go, const std::string& path, bool gamma = false) : Component(nullptr), gammaCorrection(gamma) {
            gameObjects->insert(go);

            loadModel(path);
        }

        void destruct(GameObject* go) override;

        void useShader(const std::string& name) {
            shader = Shader::collection.find(name)->second;
        }

        std::function<void()> beforeRenderFunc;
        std::function<void()> afterRenderFunc;

    private:
        std::vector<Texture3D> loaded;
        void loadModel(const std::string& name);
        void processNode(aiNode* node, const aiScene* scene);
        std::vector<Texture3D> loadMaterialTextures(aiMaterial* mat, aiTextureType textureType, std::string typeName, const aiScene*);
        size_t TextureFromFile(const char *path, const std::string &directory, bool gamma);
    };
}
