#pragma once

#include <Base.h>

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <assimp/material.h>

#include "GLObjID.h"

namespace lambda {
/*!
* @brief A texture loaded into GL
*/
struct Texture {
    Texture(const fs::path& dir, aiTextureType type, aiMaterial* parent, u32 idx);
    Texture(const Texture&) = delete;
    Texture(Texture&&) = default;
    ~Texture();
   
    GLObjID          ID{};
    aiTextureType    Type{};
    aiTextureMapping Mapping{};
    u32              UVIdx{};
    Real             Blend{};
    aiTextureOp      Op{};
    aiTextureMapMode MapMode{}; //< AKA wrapping mode
    GLsizei          Width, Height;
};
};