#include "ModelLoader.h"
#include "Model.h"
#include <iostream>

#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace lambda {
std::shared_ptr<Model> ModelLoader::Load(const fs::path& file) {
    std::cout << "Curr path: " << fs::current_path().string();

    const auto path = "Data/Assets/Models" / file;

    Assimp::Importer importer{};
    const auto scene = importer.ReadFile(path.string(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
        throw std::runtime_error{ "Scene is incomplete!" };
    }
    
    return std::make_shared<Model>(path.parent_path(), scene);
}
};
