#pragma once

#include <Base.h>
#include "Texture.h"

#include <assimp/color4.h>

namespace fs = std::filesystem;

struct aiScene;
struct aiMaterial;


namespace lambda {
class ShaderProgram;

/*!
 * @brief A material consists of a texture and a few other settings [Like color, diffuse, specular etc]
*/
class Material {
public:
    Material(const fs::path& dir, aiMaterial* mat);

    void BindToShader(ShaderProgram& shdr);

public:
    std::string Name;

    std::vector<Texture> Textures{};
   
    aiColor4D DiffuseColor{};      // AI_MATKEY_COLOR_DIFFUSE
    aiColor4D AmbientColor{};      // AI_MATKEY_COLOR_AMBIENT
    aiColor4D SpecularColor{};     // AI_MATKEY_COLOR_SPECULAR
    aiColor4D EmissiveColor{};     // AI_MATKEY_COLOR_EMISSIVE
    aiColor4D TransparentColor{};  // AI_MATKEY_COLOR_TRANSPARENT
    aiColor4D ReflectiveColor{};   // AI_MATKEY_COLOR_REFLECTIVE

    Real Shininess{};         // AI_MATKEY_SHININESS
    Real ShininessStrength{}; // AI_MATKEY_SHININESS_STRENGTH
    Real Refract{};           // AI_MATKEY_REFRACTI
    Real Reflectivity{};      // AI_MATKEY_REFLECTIVITY
};
};
