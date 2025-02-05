#include "Material.h"

#include <assimp/material.h>
#include "Texture.h"
#include "ShaderProgram.h"

namespace lambda {
Material::Material(const fs::path& dir, aiMaterial* mat) :
    Name{ mat->GetName().C_Str() }
{
    // Get material properties
    mat->Get(AI_MATKEY_COLOR_DIFFUSE, this->DiffuseColor);
    mat->Get(AI_MATKEY_COLOR_AMBIENT, this->AmbientColor);
    mat->Get(AI_MATKEY_COLOR_SPECULAR, this->SpecularColor);
    mat->Get(AI_MATKEY_COLOR_EMISSIVE, this->EmissiveColor);
    mat->Get(AI_MATKEY_COLOR_TRANSPARENT, this->TransparentColor);
    mat->Get(AI_MATKEY_COLOR_REFLECTIVE, this->ReflectiveColor);
    mat->Get(AI_MATKEY_SHININESS, this->Shininess);
    mat->Get(AI_MATKEY_SHININESS_STRENGTH, this->ShininessStrength);
    mat->Get(AI_MATKEY_REFRACTI, this->Refract);
    mat->Get(AI_MATKEY_REFLECTIVITY, this->Reflectivity);

    // Load textures - No need to make differentiation between the different textures [for now anyways]
    const auto LoadTexturesOfType = [&, this](aiTextureType type) {
        const auto cnt = mat->GetTextureCount(type);
        this->Textures.reserve(cnt + Textures.size());
        for (auto i = 0; i < cnt; i++) {
            this->Textures.emplace_back(dir, type, mat, i);
        }
    };
    LoadTexturesOfType(aiTextureType_DIFFUSE);
    LoadTexturesOfType(aiTextureType_SPECULAR);
    LoadTexturesOfType(aiTextureType_NORMALS);
    LoadTexturesOfType(aiTextureType_HEIGHT);
}

void Material::BindToShader(ShaderProgram& shdr) {
    u32 suffixes[32]{}; // Suffixes by texture type [indexed by aiTextureType]
    for (size_t i = 0; i < Textures.size(); i++) {
        const auto& t = Textures[i];
        glActiveTexture(GL_TEXTURE0 + i);

        // Calculate uniform variable name based on texture type
        const auto name = [&t] {
            switch (t.Type) {
            case aiTextureType_DIFFUSE: return "texture_diffuse";
            case aiTextureType_SPECULAR: return "texture_specular";
            case aiTextureType_AMBIENT: return "texture_ambient";
            case aiTextureType_EMISSIVE: return "texture_emissive";
            case aiTextureType_HEIGHT: return "texture_height";
            case aiTextureType_NORMALS: return "texture_normal";
            case aiTextureType_SHININESS: return "texture_shininess";
            case aiTextureType_OPACITY: return "texture_opacity";
            case aiTextureType_DISPLACEMENT: return "texture_displacement";
            case aiTextureType_LIGHTMAP: return "texture_lightmap";
            case aiTextureType_REFLECTION: return "texture_reflection";
            case aiTextureType_BASE_COLOR: return "texture_base_color";
            case aiTextureType_NORMAL_CAMERA: return "texture_normal_camera";
            case aiTextureType_EMISSION_COLOR: return "texture_emission_color";
            case aiTextureType_METALNESS: return "texture_metalness";
            case aiTextureType_DIFFUSE_ROUGHNESS: return "texture_diffuse_roughness";
            case aiTextureType_AMBIENT_OCCLUSION: return "texture_ambient_occlusion";
            }
            LAMBDA_UNREACHABLE();
        };
        char uniformName[1024];
        *std::format_to(uniformName, "{}{}", name(), ++suffixes[t.Type]) = 0;

        // Now set the sampler to the correct texture unit
        shdr.Set(uniformName, (GLint)i);
        
        // And finally bind the texture
        glBindTexture(GL_TEXTURE_2D, t.ID);
    }
}
};