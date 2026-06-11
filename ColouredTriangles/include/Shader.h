#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>

class Shader
{
  public:
    Shader(const char* vertexPath, const char* fragmentPath);

    unsigned int ID;

    void use() const { glUseProgram(ID); };

    void getUniformLocation(const std::string& name, bool value) const;
};

#endif
