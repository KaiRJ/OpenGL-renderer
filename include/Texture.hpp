#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

#include <string_view>

class Texture
{
  public:
    Texture(std::string_view texturePath, int internalFormat = GL_RGB);
    ~Texture() = default;

    void Bind(int glTextureID);

  private:
    unsigned int m_textureID {};
};

#endif
