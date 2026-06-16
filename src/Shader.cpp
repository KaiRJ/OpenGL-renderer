#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

static std::string parseShader(std::string_view path);
static unsigned int createShader(unsigned int type, const char* source);
static unsigned int createShaderProgram(unsigned int vertexShader,
                                        unsigned int fragmentShader);

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    // build and compile the shader program
    // ------------------------------------
    std::string vertexSource {parseShader(vertexPath)};
    unsigned int vertexShader {createShader(GL_VERTEX_SHADER, vertexSource.data())};

    std::string fragmentSource {parseShader(fragmentPath)};
    unsigned int fragmentShader {createShader(GL_FRAGMENT_SHADER, fragmentSource.data())};

    ID = createShaderProgram(vertexShader, fragmentShader);
}

void Shader::getUniformLocation(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

// read shader code from file
// --------------------------
static std::string parseShader(std::string_view path)
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

// create a shader
// ---------------
static unsigned int createShader(unsigned int type, const char* source)
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
// -----------------------------------------------
static unsigned int createShaderProgram(unsigned int vertexShader,
                                        unsigned int fragmentShader)
{
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
