#pragma once

#include <vector>
#include <string_view>
#include <filesystem>

#include "Mesh.h"

namespace fs = std::filesystem;

struct aiNode;
struct aiScene;

namespace lambda {
class ShaderProgram;

/*!
 * @brief Represents a renderable model
*/
class Model {
public:
    Model(const fs::path& dir, const aiScene* scene);

    void Draw(ShaderProgram* shdr);

private:
    void InsertNodeMeshes(const fs::path& dir, const aiScene* scene, aiNode* node);

private:
    std::vector<Mesh> m_Meshes{};
};
};
