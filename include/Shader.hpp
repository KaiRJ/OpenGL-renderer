#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

class Shader
{
  public:
    Shader(std::string vpath, std::string fpath);
    ~Shader();

    void Bind() const;
    static void Unbind();
    void Reload();

    // Set uniforms
    void SetUniform1f(const std::string& name, float value);
    void SetUniform1i(const std::string& name, int value);
    void SetUniformMatrix4fv(const std::string& name, glm::mat4 value);

  private:
    unsigned int shader_id;
    std::string vertex_path;
    std::string fragment_path;
    std::unordered_map<std::string, int> uniform_location_cache;

    int GetUniformLocation(const std::string& name);
};

std::string parseShader(const std::string& path);
unsigned int createShader(unsigned int type, const char* source);
unsigned int createShaderProgram(const std::string& vertex_path,
                                 const std::string& fragment_path);

#endif
