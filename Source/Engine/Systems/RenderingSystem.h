#pragma once

#include <entt/fwd.hpp>
#include <glad/glad.h>

#include "Engine/ShaderProgram.h"

struct GLFWwindow;

namespace lambda {
class RenderingSystem final {
public:
    RenderingSystem(GLFWwindow* wnd);
    ~RenderingSystem() = default;

    void Update(entt::registry& registry);

private:
    ShaderProgram m_DefaultShaderProgram;
    GLFWwindow* m_Wnd{};
    GLuint      m_VAO{};
    GLuint      m_VBO{};
    GLuint      m_EBO{};

    // VkExtent2D                m_WndSz{ 1920, 1080 };
    // VkInstance*               m_vkInstance{};  // Vulkan library handle
    // VkDebugUtilsMessengerEXT* m_vkDebugMsgr{}; // Vulkan debug output handle
    // VkPhysicalDevice*         m_vkDevGPU{};    // GPU chosen as the default device
    // VkDevice*                 m_vkDevCmd{};    // Vulkan device for commands
    // VkSurfaceKHR*             m_vkWndSurf{};   // Vulkan window surface
};
};
