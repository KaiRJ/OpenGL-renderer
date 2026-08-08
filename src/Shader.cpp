#include "Shader.hpp"

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string_view>

std::string parseShader(std::string_view path);
unsigned int createShader(unsigned int type, const char* source);
unsigned int createShaderProgram(std::string_view vertexPath,
                                 std::string_view fragmentPath);

Shader::Shader(std::string vertexPath, std::string fragmentPath)
    : m_vertexPath {vertexPath}, m_fragmentPath {fragmentPath}
{
    m_shaderID = createShaderProgram(m_vertexPath, m_fragmentPath);
}

Shader::~Shader() { glDeleteProgram(m_shaderID); }

void Shader::Bind() const { glUseProgram(m_shaderID); };

void Shader::Unbind() const { glUseProgram(0); };

int Shader::GetUniformLocation(const std::string& name)
{
    if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
        return m_uniformLocationCache[name];

    int location {glGetUniformLocation(m_shaderID, name.c_str())};
    if (location == -1)
        std::cout << "Warning: uniform '" << name << " doesn't exist!" << std::endl;
    else
        m_uniformLocationCache[name] = location;

    return location;
}

void Shader::Reload()
{
    unsigned int new_programID {createShaderProgram(m_vertexPath, m_fragmentPath)};

    if (new_programID)
    {
        glDeleteProgram(m_shaderID);
        m_shaderID = new_programID;
    }
}

void Shader::SetUniform1f(const std::string& name, float value)
{
    int location {GetUniformLocation(name)};
    glUniform1f(location, value);
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    int location {GetUniformLocation(name)};
    glUniform1i(location, value);
}

// read shader code from file
std::string parseShader(std::string_view path)
{
    std::ifstream stream {path.data()};
    stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    std::stringstream ss;
    try
    {
        ss << stream.rdbuf();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    return ss.str();
}

// create a shader from source code
unsigned int createShader(unsigned int type, const char* source)
{
    unsigned int shader {glCreateShader(type)};
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    // get any debug information
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::"
                  << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT")
                  << "::COMPILATION_FAILED\n " << infoLog << std::endl;
    }

    return shader;
}

// link vertex and fragment shaders into a program
unsigned int createShaderProgram(std::string_view vertexPath,
                                 std::string_view fragmentPath)
{
    // build and compile the shaders
    std::string vertexSource {parseShader(vertexPath)};
    unsigned int vertexShader {createShader(GL_VERTEX_SHADER, vertexSource.data())};

    std::string fragmentSource {parseShader(fragmentPath)};
    unsigned int fragmentShader {createShader(GL_FRAGMENT_SHADER, fragmentSource.data())};

    // link shaders to shader program
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // get any debug information
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}
