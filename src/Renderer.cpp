#include "Renderer.h"

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::Clear(float r, float g, float b, float a) const
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& va, const Shader& s, int count) const
{
    va.Bind();
    s.Bind();
    glDrawArrays(GL_TRIANGLES, 0, count);
}

// shaderProgram1.SetUniform1f("u_time_s", glfwGetTime());
// shaderProgram2.SetUniform1f("u_time_s", glfwGetTime());
