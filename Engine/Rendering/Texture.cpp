
#include "EngineCommon.h"
#include "Texture.hpp"
#include "opengl.hpp"
#include "stb_image.h"

namespace Game
{

Texture::Texture(const std::string& filepath)
    : rendererId(0), filepath(filepath), buffer(nullptr), width(0), height(0), bpp(0)
{
    stbi_set_flip_vertically_on_load(1);
    buffer = stbi_load(filepath.c_str(), &width, &height, &bpp, 4);

    GLCall(glGenTextures(1, &rendererId));
    GLCall(glBindTexture(GL_TEXTURE_2D, rendererId));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    if (buffer)
        stbi_image_free(buffer);
}

Texture::~Texture()
{
    GLCall(glDeleteTextures(1, &rendererId));
}

void Texture::Bind(unsigned int slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, rendererId));
}

void Texture::Unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

}