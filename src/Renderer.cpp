#include "Renderer.hpp"
#include "Debug.hpp"
#include "IndexBuffer.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stdexcept>

static void loadOpenglPointers();

Renderer::Renderer()
{
    loadOpenglPointers();
    initialiseDebugOutput();
    glEnable(GL_DEPTH_TEST);
}

void Renderer::clear(float r, float g, float b, float a) const
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw(const VertexArray& va, const Shader& s, int count) const
{
    va.Bind();
    s.Bind();
    glDrawArrays(GL_TRIANGLES, 0, count);
}

void Renderer::draw(const VertexArray& va, const Shader& s, const IndexBuffer& ib) const
{
    va.Bind();
    s.Bind();
    ib.Bind();
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0);
}

static void loadOpenglPointers()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }
}
