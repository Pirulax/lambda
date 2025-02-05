#pragma once

#include <filesystem>
#include <memory>

#include <assimp/Importer.hpp>

namespace fs = std::filesystem;


namespace lambda {
class Model;
class ModelLoader {
public:
    ModelLoader()  = default;
    ~ModelLoader() = default;

    std::shared_ptr<Model> Load(const fs::path& file);

private:
    Assimp::Importer m_AIImporter{};
};
};
