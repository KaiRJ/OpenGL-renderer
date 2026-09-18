#include "Texture.hpp"
#include "stb_image.h"

#include <iostream>

Texture::Texture(std::string_view path, int format)
{
    // flip the y-axis when loading images
    stbi_set_flip_vertically_on_load(true);

    // generate texture
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    // set some defaults
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load texture
    int width;
    int height;
    int n_channels;
    unsigned char* data = stbi_load(path.data(), &width, &height, &n_channels, 0);
    if (data != nullptr)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE,
                     data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << "\n";
    }

    // free data as don't need it anymore
    stbi_image_free(data);
}

Texture::~Texture() { glDeleteTextures(1, &m_textureID); }

void Texture::Bind(int slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}
