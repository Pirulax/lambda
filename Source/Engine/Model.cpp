#include "Model.h"

#include "ShaderProgram.h"

#include <ranges>
namespace rng = std::ranges;

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace lambda {
Model::Model(const fs::path& dir, const aiScene* scene) {
    InsertNodeMeshes(dir, scene, scene->mRootNode);
}

void Model::Draw(ShaderProgram* shdr) {
    for (auto& m : m_Meshes) {
        if (shdr) {
            m.BindToShader(*shdr);
        }
        m.Draw();
    }
}

void Model::InsertNodeMeshes(const fs::path& dir, const aiScene* scene, aiNode* node) {
    // Process meshes in this node
    for (u32 i = 0; i < node->mNumMeshes; i++) {
         m_Meshes.emplace_back(dir, scene, scene->mMeshes[node->mMeshes[i]]);
    }

    // Recurse into children nodes
    for (u32 i = 0; i < node->mNumChildren; i++) {
        InsertNodeMeshes(dir, scene, node->mChildren[i]);
    }
}
};
