#include "Shader.hpp"
#include <cassert>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>

Shader::Shader(std::string vpath, std::string fpath)
    : vertex_path {std::move(vpath)}, fragment_path {std::move(fpath)}
{
    shader_id = createShaderProgram(vertex_path, fragment_path);
}

Shader::~Shader() { glDeleteProgram(shader_id); }

void Shader::Bind() const { glUseProgram(shader_id); };

void Shader::Unbind() { glUseProgram(0); };

void Shader::Reload()
{
    unsigned int new_program_id {createShaderProgram(vertex_path, fragment_path)};
    if (static_cast<bool>(new_program_id))
    {
        glDeleteProgram(shader_id);
        shader_id = new_program_id;
    }
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (uniform_location_cache.contains(name))
    {
        return uniform_location_cache[name];
    }

    int location {glGetUniformLocation(shader_id, name.c_str())};
    if (location == -1)
    {
        std::cout << "Warning: uniform '" << name << " doesn't exist!\n";
    }
    else
    {
        uniform_location_cache[name] = location;
    }

    return location;
}

void Shader::SetUniform1f(const std::string& name, float value)
{
    Bind();
    int location {GetUniformLocation(name)};
    glUniform1f(location, value);
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    Bind();
    int location {GetUniformLocation(name)};
    glUniform1i(location, value);
}

void Shader::SetUniformMatrix4fv(const std::string& name, glm::mat4 value)
{
    Bind();
    int location = GetUniformLocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

// read shader code from file
std::string parseShader(const std::string& path)
{
    std::ifstream stream {path.c_str()};
    stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    std::stringstream sstream;
    try
    {
        sstream << stream.rdbuf();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n";
    }

    return sstream.str();
}

// create a shader from source code
unsigned int createShader(unsigned int type, const char* source)
{
    unsigned int shader {glCreateShader(type)};
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    // get any debug information
    int success;
    char info_log[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!static_cast<bool>(success))
    {
        glGetShaderInfoLog(shader, 512, nullptr, info_log);
        std::cout << "ERROR::SHADER::"
                  << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT")
                  << "::COMPILATION_FAILED\n " << info_log << "\n";
    }

    return shader;
}

// link vertex and fragment shaders into a program
unsigned int createShaderProgram(const std::string& vertex_path,
                                 const std::string& fragment_path)
{
    // build and compile the shaders
    std::string vertex_source {parseShader(vertex_path)};
    unsigned int vertex_shader {createShader(GL_VERTEX_SHADER, vertex_source.data())};

    std::string fragment_source {parseShader(fragment_path)};
    unsigned int fragment_shader {
        createShader(GL_FRAGMENT_SHADER, fragment_source.data())};

    // link shaders to shader program
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    // get any debug information
    int success;
    char info_log[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!static_cast<bool>(success))
    {
        glGetProgramInfoLog(program, 512, nullptr, info_log);
        std::cout << "ERROR::SHADER::PROGRRAM::LINKING_FAILED\n" << info_log << "\n";
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return program;
}
