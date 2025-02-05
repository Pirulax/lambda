#pragma once

#include <string>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <Base.h>
#include "Material.h"
#include "GLObjID.h"

struct aiMesh;
struct aiScene;

namespace lambda {
class ShaderProgram;

struct Vertex {
    using Index = u32;
    static constexpr auto GLIndexType = GL_UNSIGNED_INT;

    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexUV; // We're using the 0th UV channel only for now
};

class Mesh {
public:
    Mesh(const fs::path& dir, const aiScene* scene, aiMesh* mesh);
    Mesh(const Mesh&) = delete;
    Mesh(Mesh&&) = default;

    ~Mesh();

    void Draw();
    void BindToShader(ShaderProgram& shdr);
private:
    GLObjID     m_VAO{}; // Vertex Array Object - Vertex attributes - Bind this to draw the object
    GLObjID     m_VBO{}; // Vertex Buffer Object - Vertex buffer
    GLObjID     m_EBO{}; // Element Buffer Object - Index buffer
    size_t      m_IdxCnt{};
    Material    m_Material;
    std::string m_Name{};
};
};