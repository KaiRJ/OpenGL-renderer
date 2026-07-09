#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <unordered_map>

class Shader
{
  public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void Reload(const char* vertexPath, const char* fragmentPath);

    // Set uniforms
    void SetUniform1f(const std::string& name, float value);

  private:
    unsigned int m_shaderID {};
    std::unordered_map<std::string, int> m_uniformLocationCache {};

    int GetUniformLocation(const std::string& name);
};

#endif
