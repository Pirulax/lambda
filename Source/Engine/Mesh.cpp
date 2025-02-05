#include "Mesh.h"
#include "ShaderProgram.h"

#include <glad/glad.h>
#include <assimp/scene.h>

namespace lambda {
Mesh::Mesh(const fs::path& dir, const aiScene* scene, aiMesh* mesh) :
    m_Material{ dir, scene->mMaterials[mesh->mMaterialIndex] }, // TODO: Waste of memory to instantiate the same material if used by mutliple meshes
    m_Name{ mesh->mName.C_Str() }
{
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    // Index buffer
    {
        std::vector<u32> indices{};
        indices.reserve(mesh->mNumFaces * 3); // Most of the time we're dealing with triangles
        for (u32 f = 0; f < mesh->mNumFaces; f++) {
            const auto m = &mesh->mFaces[f];
            for (u32 i = 0; i < m->mNumIndices; i++) {
                indices.push_back(m->mIndices[i]);
            }
        }
        glGenBuffers(1, &m_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * indices.size(), indices.data(), GL_STATIC_DRAW);
    }
    
    // Vertex buffer
    {
        std::vector<Vertex> vertices;
        for (u32 i = 0; i < mesh->mNumVertices; i++) {
            const auto p = &mesh->mVertices[i];
            const auto n = mesh->mNormals ? &mesh->mNormals[i] : nullptr;
            const auto t = mesh->mTextureCoords ? &mesh->mTextureCoords[0][i] : nullptr;
            vertices.emplace_back(
                glm::vec3{ p->x, p->y, p->z },
                n ? glm::vec3{ n->x, n->y, n->z } : glm::vec3{},
                t ? glm::vec2{ t->x, t->y } : glm::vec2{}
            );
        }
        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(aiVector3D) * mesh->mNumVertices, mesh->mVertices, GL_STATIC_DRAW);

        // Vertex Position
        glEnableVertexAttribArray(0);	
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));

        // Vertex Normal
        glEnableVertexAttribArray(1);	
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

        // Vertex Texture UV
        glEnableVertexAttribArray(2);	
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexUV));

    }
    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE); // Unbind VAO
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

void Mesh::Draw() {
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_IdxCnt, Vertex::GLIndexType, NULL);
}

void Mesh::BindToShader(ShaderProgram& shdr) {
    m_Material.BindToShader(shdr);
}
};
