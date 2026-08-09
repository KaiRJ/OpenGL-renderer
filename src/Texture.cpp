#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#include <iostream>

Texture::Texture(std::string_view texturePath, int internalFormat)
{
    // flip the y-axis when loading images
    stbi_set_flip_vertically_on_load(true);

    // generate texture and set some defaults
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load(texturePath.data(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, internalFormat,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    // free data as don't need it anymore
    stbi_image_free(data);
}

void Texture::Bind(int glTextureID)
{
    glActiveTexture(glTextureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}
