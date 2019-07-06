#define GL_GLEXT_PROTOTYPES
#include "PhysicsDebugDraw.hpp"


#include "../EngineManager.hpp"
#include "../System/RenderSystem.hpp"
#include "../Settings.hpp"

#include <SDL.h>
#include <SDL_opengl.h>
#include <vector>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

#include "DebugDrawShader.vert" //TODO: this should not be in reasese
#include "DebugDrawShader.frag" //TODO: this should not be in release

namespace wlEngine {
    PhysicsDebugDraw::PhysicsDebugDraw() : shader(vertexCode, fragmentCode) {
		
        windowWidth = RenderSystem::get()->windowWidth;
        windowHeight = RenderSystem::get()->windowHeight;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
    }

    void PhysicsDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {

    }

    void PhysicsDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
        auto camera = EngineManager::getwlEngine()->getCurrentScene()->getCamera();

        std::vector<float> glVertices(vertexCount * 2);
        shader.use();
        for (int i = 0; i < vertexCount; i++) {
            glVertices[2 * i] = vertices[i].x;
            glVertices[2 * i + 1] = vertices[i].y;
        }
		
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, glVertices.size() * sizeof(float), glVertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glm::mat4 proj = glm::mat4(1.0f);
        glm::mat4 cameraView = camera->getViewMatrix();

#if SETTINGS_GAME_DIMENSION == 0
            proj = glm::perspective(glm::radians(45.0f), (float)windowWidth / windowHeight, 0.1f, 100000.0f);
        
#else
			proj = glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight, -1.0f, 1000.0f);
#endif
        shader.setMat4("view", cameraView);
        shader.setMat4("projection", proj);
        shader.setVec3("color", glm::vec3(color.r, color.g, color.b));

        glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
    }
    void PhysicsDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {
        B2_NOT_USED(center);
        B2_NOT_USED(radius);
        B2_NOT_USED(color);
    }
    void PhysicsDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {
        B2_NOT_USED(center);
        B2_NOT_USED(radius);
        B2_NOT_USED(color);
        B2_NOT_USED(axis);
    }
    void PhysicsDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
        B2_NOT_USED(p1);
        B2_NOT_USED(p2);
        B2_NOT_USED(color);
    }
    void PhysicsDebugDraw::DrawTransform(const b2Transform& xf) {
        B2_NOT_USED(xf);
    }

    void PhysicsDebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) {
        B2_NOT_USED(p);
        B2_NOT_USED(size);
        B2_NOT_USED(color);
    }
}
