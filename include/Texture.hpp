#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

#include <string_view>

class Texture
{
  public:
    Texture(std::string_view path, int format = GL_RGB);
    ~Texture();

    void Bind(int slot = 0);

  private:
    unsigned int m_textureID {};
};

#endif
