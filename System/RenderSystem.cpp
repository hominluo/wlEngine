#include "../Component/Sprite.hpp"
#include "../Component/Transform.hpp"
#include "../Component/Animation.hpp"
#include "../Component/Model.hpp"
#include "../EngineManager.hpp"
#include "../Settings.hpp"

#include "UISystem.hpp"

namespace wlEngine {
    RenderSystem* RenderSystem::renderSystem = nullptr;

    RenderSystem::RenderSystem() {
        if (Settings::settings["perspective"]) {
            projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / windowHeight, 0.1f, 100000.0f);
            perspective = true;
        }
        else {
            projection = glm::ortho(0.0f, (float)windowWidth , 0.0f, (float)windowHeight, -1.0f, 1000.0f);
            perspective = false;
        }

        if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
            std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
            exit(-1);
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
        stbi_set_flip_vertically_on_load(true);
        window = SDL_CreateWindow("OpenGL Test", 50, 50, windowWidth, windowHeight, SDL_WINDOW_OPENGL);
        glContext = SDL_GL_CreateContext(window);
        gladLoadGLLoader(SDL_GL_GetProcAddress);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_STENCIL_TEST);
        glEnable(GL_BLEND);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

        glClearStencil(0);

        registerSystem(this);
    }
    RenderSystem* RenderSystem::get() {
        return renderSystem;
    } 

    void RenderSystem::init() {
        renderSystem = new RenderSystem();
    }

    void RenderSystem::render() {
        beginRenderScene();
        if(perspective) {
            for (auto c : Model::collection) {
                render(c);
            }
        }

        for (auto c : Sprite::collection) {
            render(c);
        }

        UISystem::get()->render();
        EngineManager::getwlEngine()->getCurrentScene()->getWorld()->DrawDebugData(); //TODO: has to be removed
        endRenderScene();
    }

    void RenderSystem::render(Sprite* t) {
        auto camera = EngineManager::getwlEngine()->getCurrentScene()->getCamera();

        t->mShader->use();

        glBindTexture(GL_TEXTURE_2D, t->mTexture);

        t->mShader->setMat4("model", t->gameObject->getComponent<Transform>()->getModel());
        t->mShader->setMat4("view", camera->getViewMatrix());
        t->mShader->setMat4("projection", projection);
        glBindVertexArray(t->VAO);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void RenderSystem::render(Model* model) {
        for (auto& gameObject : *model->gameObjects) {

            if (model->beforeRenderFunc) model->beforeRenderFunc();
            auto shader = model->shader;
            auto transform = gameObject->getComponent<Transform>();
            auto camera = EngineManager::getwlEngine()->getCurrentScene()->getCamera();
            auto modelMatrix = transform->getModel();
            auto view = camera->getViewMatrix();

            shader->use();
            shader->setMat4("model", modelMatrix);
            shader->setMat4("view", view);
            shader->setMat4("projection", projection); 
            shader->setVec3("viewPos", camera->getComponent<Transform>()->position);

            for (auto& mesh : model->meshes) {
                // bind appropriate textures
                unsigned int diffuseNr  = 1;
                unsigned int specularNr = 1;
                unsigned int normalNr   = 1;
                unsigned int heightNr   = 1;
                for(unsigned int i = 0; i < mesh.textures.size(); i++)
                {
                    glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
                    // retrieve texture number (the N in diffuse_textureN)
                    std::string number;
                    std::string name = mesh.textures[i].type;
                    if(name == "texture_diffuse")
                        number = std::to_string(diffuseNr++);
                    else if(name == "texture_specular")
                        number = std::to_string(specularNr++); // transfer unsigned int to stream
                    else if(name == "texture_normal")
                        number = std::to_string(normalNr++); // transfer unsigned int to stream
                    else if(name == "texture_height")
                        number = std::to_string(heightNr++); // transfer unsigned int to stream

                    // now set the sampler to the correct texture unit
                    glUniform1i(glGetUniformLocation(model->shader->ID, (name + number).c_str()), i);
                    // and finally bind the texture
                    glBindTexture(GL_TEXTURE_2D, mesh.textures[i].id);
                }
                //
                // draw mesh
                glBindVertexArray(mesh.VAO);
                glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
                glBindVertexArray(0);

                // always good practice to set everything back to defaults once configured.
                glActiveTexture(GL_TEXTURE0);
                if (model->afterRenderFunc) model->afterRenderFunc();
            }
        }

    }

    void RenderSystem::endRenderScene(){
        SDL_GL_SwapWindow(window);
    }

    void RenderSystem::beginRenderScene(){
        //glViewport(0, 0, winWidth, winHeight);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    void RenderSystem::update() {
        render();
    }

}