#include "Renderer.hpp"
#include "IndexBuffer.hpp"

Renderer::Renderer() { glEnable(GL_DEPTH_TEST); }

void Renderer::Clear(float r, float g, float b, float a) const
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& va, const Shader& s, int count) const
{
    va.Bind();
    s.Bind();
    glDrawArrays(GL_TRIANGLES, 0, count);
}

void Renderer::Draw(const VertexArray& va, const Shader& s, const IndexBuffer& ib) const
{
    va.Bind();
    s.Bind();
    ib.Bind();
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0);
}
