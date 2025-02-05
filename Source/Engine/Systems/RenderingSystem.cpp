#include "RenderingSystem.h"

#include <iostream>
#include <vector>
#include <entt/entt.hpp>

//#define GLFW_DLL
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include <Engine/Components/ModelComponent.h>
#include "Engine/Shader.h"
#include "Engine/ShaderProgram.h"

namespace lambda {
RenderingSystem::RenderingSystem(GLFWwindow* wnd) :
    m_Wnd{wnd},
    m_DefaultShaderProgram{
        lambda::FragmentShader::FromString(
            R"(
                #version 330 core

                out vec4 frag;

                void main() {
                   frag = vec4(1.0f, 0.5f, 0.2f, 1.0f);
                }
            )"
        ),
        lambda::VertexShader::FromString(
            R"(
                #version 330 core
                layout (location = 0) in vec3 aPos;
                void main() {
                    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
                }
            )"
        )
    }
{
    glfwSetFramebufferSizeCallback(m_Wnd, [](GLFWwindow*, GLsizei w, GLsizei h) {
        glViewport(0, 0, w, h);
    });
}

void RenderingSystem::Update(entt::registry& registry) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_DefaultShaderProgram.Use();

    for (auto [entity, mesh] : registry.view<lambda::ModelComponent>().each()) {
        mesh.Draw(&m_DefaultShaderProgram);
    }

    glfwSwapBuffers(m_Wnd);
    glfwPollEvents();
}
};
