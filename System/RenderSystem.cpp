#define GL_GLEXT_PROTOTYPES
#include "RenderSystem.hpp"

#include "../EngineManager.hpp"

#include "../Component/Sprite.hpp"
#include "../Component/Transform.hpp"
#include "../Component/Animation.hpp"
#include "../Component/Model.hpp"
#include "../Component/Text.hpp"

#include "../GameEditor/GameEditor.hpp"

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_sdl.h"
#include "../imgui/imgui_impl_opengl3.h"

#include <glad/glad.h>
namespace wlEngine {
    RenderSystem* RenderSystem::renderSystem = nullptr;

    RenderSystem::RenderSystem() {
        //settings
#if SETTINGS_GAME_DIMENSION == 1
        projection = glm::perspective(glm::radians(45.0f), (float)sceneWidth / sceneHeight, 0.1f, 100000.0f);
#else
#endif

        gameEditor = new GameEditor;
        //SDL and OpenGL init
        SDLInit();
        ImGuiInit();   

        registerSystem(this);
    }

    RenderSystem::~RenderSystem() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();


#if SETTINGS_ENGINEMODE
        glDeleteFramebuffers(1,&sceneFramebuffer);
        glDeleteTextures(1, &sceneTexture);
        glDeleteTextures(1, &depthAndStencilTexture);
#endif
    }

    RenderSystem* RenderSystem::get() {
        return renderSystem;
    } 

    void RenderSystem::init() {
        renderSystem = new RenderSystem();
    }

    void RenderSystem::render() {
#if SETTINGS_GAME_DIMENSION==0
        camera2D = EngineManager::getwlEngine()->getCurrentScene()->getCamera()->getComponent<Camera2D>();
#endif

#if SETTINGS_ENGINEMODE
        glBindFramebuffer(GL_FRAMEBUFFER, sceneFramebuffer);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glViewport(0,0, sceneWidth, sceneHeight);
        renderGame();
        EngineManager::getwlEngine()->getCurrentScene()->getWorld()->DrawDebugData(); //TODO: has to be removed

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glViewport(0, 0, windowWidth, windowHeight);
        renderGameEditor();
#else
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glViewport(0, 0, windowWidth, windowHeight);
        renderGame();
#endif

        SDL_GL_SwapWindow(window);
    }




    void RenderSystem::update() {
        render();
    }

    int RenderSystem::windowResizeCallbackWrapper(void* data, SDL_Event* event) {
        if(renderSystem)
            return renderSystem->windowResizeCallback(data, event);
        return 0;
    }

    int RenderSystem::windowResizeCallback(void* data, SDL_Event* event) {
        if(event->type == SDL_WINDOWEVENT) {
            switch (event->window.event) {
                case SDL_WINDOWEVENT_RESIZED:
                    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
                    break;
            }
        }

        return 0;
    }

    void RenderSystem::setViewPort(int x, int y, int width, int height) {
        glViewport(x,y,width,height);
    }


    void RenderSystem::SDLInit() {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
        stbi_set_flip_vertically_on_load(true);

        int SDL_Flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
#if SETTINGS_ENGINEMODE == 0
        windowWidth = sceneWidth;
        windowHeight = sceneHeight;
#endif
        window = SDL_CreateWindow("OpenGL Test", 150, 50, windowWidth, windowHeight, SDL_Flags);
        glContext = SDL_GL_CreateContext(window);
        SDL_AddEventWatch(windowResizeCallbackWrapper, window);
        gladLoadGLLoader(SDL_GL_GetProcAddress);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_STENCIL_TEST);
        glEnable(GL_BLEND);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

#if SETTINGS_ENGINEMODE
        glGenFramebuffers(1, &sceneFramebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, sceneFramebuffer);

        //sceneTexture
        glGenTextures(1, &sceneTexture);
        glBindTexture(GL_TEXTURE_2D, sceneTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sceneWidth, sceneHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, sceneTexture, 0);

        //depth and stencil texture
        glGenTextures(1, &depthAndStencilTexture);
        glBindTexture(GL_TEXTURE_2D, depthAndStencilTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, sceneWidth, sceneHeight, 0,
                GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthAndStencilTexture, 0);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_STENCIL_TEST);
        glEnable(GL_BLEND);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
#endif
        glClearStencil(0);
    }

    void RenderSystem::ImGuiInit() {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        ImGui::StyleColorsDark();
        ImGui_ImplSDL2_InitForOpenGL(window, &glContext);

        ImGui_ImplOpenGL3_Init("#version 450");

    }
#if SETTINGS_ENGINEMODE
    void RenderSystem::renderGameEditor() {
        ImGui_ImplOpenGL3_NewFrame();   
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        void* data[3];
        data[0] = &sceneTexture;
        data[1] = &sceneWidth;
        data[2] = &sceneHeight;
        gameEditor->render(data);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
#endif

    /* Render *************/
    void RenderSystem::renderGame() {
#if SETTINGS_GAME_DIMENSION == 1
        for (auto c : Model::collection) {
            render(c);
        }
#endif

        for (auto c : Sprite::collection) {
            render(c);
        }

        for (auto text : Text::collection) {
            render(text);
        }
    }

    void RenderSystem::render(Text* t) {
        t->shader->use();
        //
        //main texture
        glActiveTexture(GL_TEXTURE0);
		auto model = t->entity->getComponent<Transform>()->getModel();
		auto cameraMatrix = camera2D->getTransformMatrix();
		for (auto& character : t->text) {
			glBindTexture(GL_TEXTURE_2D, character.texture->mTexture);

			t->shader->setMat4("model", model * character.getTextTransform());
			t->shader->setMat4("view", cameraMatrix.view);
			t->shader->setMat4("projection", cameraMatrix.projection);
			glBindVertexArray(character.texture->VAO);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
       

        //glBindTexture(GL_TEXTURE_2D, 0);
        //glBindVertexArray(0);
    }

    void RenderSystem::render(Sprite* t) {
        int i = 0;
        t->shader->use();
        if(t->beforeRenderFunc)t->beforeRenderFunc();
        //
        //main texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, t->mainTexture->mTexture);
        auto animation = t->entity->getComponent<Animation>();
        if (animation) t->mainTexture->clip(animation->getCurrentClip(),true);

        //other textures
        for(auto& texture : t->textures) {
            i++;
            glActiveTexture(GL_TEXTURE0  + i);
            glBindTexture(GL_TEXTURE_2D, texture.second->mTexture);
            if (animation) texture.second->clip(animation->getCurrentClip(),true);
            t->shader->setInt(texture.first, i);
        }

        t->shader->setMat4("model", t->entity->getComponent<Transform>()->getModel());
        t->shader->setMat4("view", camera2D->getTransformMatrix().view);
        t->shader->setMat4("projection", camera2D->getTransformMatrix().projection);
        glBindVertexArray(t->mainTexture->VAO);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        if(t->afterRenderFunc)t->afterRenderFunc();
        //glActiveTexture(GL_TEXTURE0);
        //glBindTexture(GL_TEXTURE_2D, 0);
        //glBindVertexArray(0);
    }

    void RenderSystem::render(Model* model) {
        for (auto& gameObject : *model->entities) {

            if (model->beforeRenderFunc) model->beforeRenderFunc();
            auto shader = model->shader;
            auto transform = gameObject->getComponent<Transform>();
            auto modelMatrix = transform->getModel();
            auto maxtrix = camera2D->getTransformMatrix(); //shuold be 3D

            shader->use();
            shader->setMat4("model", modelMatrix);
            shader->setMat4("view", maxtrix.view);
            shader->setMat4("projection", maxtrix.projection);
            shader->setVec3("viewPos", camera2D->transform->position); // should be 3D

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
}
