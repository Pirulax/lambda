#include <iostream>
#include <Windows.h>
#include <debugapi.h>
#include <entt/entt.hpp>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include <memory>

#include <Engine/Components/ModelComponent.h>
#include <Engine/Systems/RenderingSystem.h>
#include <Engine/ModelLoader.h>

int main() {
    while (!IsDebuggerPresent()) {
        std::cout << "waiting for debugger";
    }
    std::cout << "Hello!";

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    const auto wnd = glfwCreateWindow(1'920, 1'080, "LearnOpenGL", NULL, NULL);
    if (!wnd) {
        std::cout << "Failed to create GLFW window" << std::endl;
        return 1;
    }
    glfwMakeContextCurrent(wnd);

    // Load all OpenGL function pointers using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return 2;
    }

    lambda::RenderingSystem renderingSys{wnd};
    
    entt::registry reg{};

    //const auto triMesh = std::shared_ptr<lambda::Mesh>(new lambda::Mesh{
    //    {
    //        {0.5f,   0.5f, 0.0f},  // top right
    //        {0.5f,  -0.5f, 0.0f},  // bottom right
    //        {-0.5f, -0.5f, 0.0f},  // bottom left
    //        {-0.5f,  0.5f, 0.0f}   // top left 
    //    },
    //    { 
    //        0, 1, 3,  // first Triangle
    //        //1, 2, 3   // second Triangle
    //    }
    //});
    //

    lambda::ModelLoader ml{};
    const auto grenade = ml.Load("LeBomb/LeBomb.obj");

    const auto e = reg.create();
    reg.emplace<lambda::ModelComponent>(e, grenade);

    while (true) {
        renderingSys.Update(reg);
    }
    
    return 0;
}
