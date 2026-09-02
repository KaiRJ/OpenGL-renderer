#ifndef RENDERER_H
#define RENDERER_H

#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"

class Renderer
{
  public:
    Renderer();
    ~Renderer() = default;

    void clear(float r = 0.2f, float g = 0.3f, float b = 0.3f, float a = 1.0f) const;
    void draw(const VertexArray& va, const Shader& s, int count) const;
    void draw(const VertexArray& va, const Shader& s, const IndexBuffer& ib) const;
};

#endif
