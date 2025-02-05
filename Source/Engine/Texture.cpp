#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace lambda {
Texture::Texture(const fs::path& dir, aiTextureType type, aiMaterial* parent, u32 idx) :
    Type{type}
{
    aiString fileName{};
    parent->GetTexture(
        type, 
        idx, 
        &fileName,
        &this->Mapping,
        &this->UVIdx,
        &this->Blend,
        &this->Op,
        &this->MapMode
    );

    stbi_set_flip_vertically_on_load(true);
    int n;
    const auto img = stbi_load((dir / fileName.C_Str()).string().c_str(), &Width, &Height, &n, 0);
    if (!img) {
        throw std::runtime_error{ "Failed to load image!" };
    }

    glGenTextures(1, &this->ID);
    if (!this->ID) {
        stbi_image_free(img);
        throw std::bad_alloc{};
    }

    glBindTexture(GL_TEXTURE_2D, this->ID);

    constexpr u32 formats[]{ GL_NONE, GL_RED, GL_NONE, GL_RGB, GL_RGBA };
    if (formats[n] != GL_NONE) {
        glTexImage2D(GL_TEXTURE_2D, 0, formats[n], Width, Height, 0, formats[n], GL_UNSIGNED_BYTE, img);
        assert(glGetError() == GL_NO_ERROR);
    }

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(img);
}

Texture::~Texture() {
    glDeleteTextures(1, &this->ID);
}
};
