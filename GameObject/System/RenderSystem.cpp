#include "../Component/Texture.hpp"
#include "../Component/Transform.hpp"
#include "../Component/Animation.hpp"
#include "../../EngineManager.hpp"

namespace wlEngine {
    RenderSystem* RenderSystem::renderSystem = nullptr;

    RenderSystem::RenderSystem() {
        if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
            std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
            exit(-1);
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
        SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
        stbi_set_flip_vertically_on_load(true);
        window = SDL_CreateWindow("OpenGL Test", 0, 0, windowWidth, windowHeight, SDL_WINDOW_OPENGL);
        glContext = SDL_GL_CreateContext(window);
        gladLoadGLLoader(SDL_GL_GetProcAddress);
        glEnable(GL_DEPTH_TEST);

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
        for (auto c : Texture::collection) {
            render(c);
        }
		EngineManager::getwlEngine()->getCurrentScene()->getWorld()->DrawDebugData();
        endRenderScene();
    }

    void RenderSystem::render(Texture* t) {
        auto camera = EngineManager::getwlEngine()->getCurrentScene()->getCamera();

        auto cameraView = camera->getViewMatrix();
        t->mShader.use();

        glBindTexture(GL_TEXTURE_2D, t->mTexture);

        glm::mat4 proj = glm::mat4(1.0f);

        if (camera->perspective) {
            proj = glm::perspective(glm::radians(45.0f), (float)windowWidth / windowHeight, 0.1f, 100000.0f);
        }
        else {
            proj = glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight, -1.0f, 1000.0f);
        }
        t->mShader.setMat4("model", t->gameObject->getComponent<Transform>()->getModel());
        t->mShader.setMat4("view", cameraView);
        t->mShader.setMat4("projection", proj);

        glBindVertexArray(t->VAO);

        glDrawArrays(GL_TRIANGLES, 0, 36);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void RenderSystem::endRenderScene(){
        SDL_GL_SwapWindow(window);
    }

    void RenderSystem::beginRenderScene(){
        //glViewport(0, 0, winWidth, winHeight);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderSystem::update() {
        render();
    }
}
