#ifndef RENDERER_H
#define RENDERER_H

#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"

namespace Renderer
{
    void initialise();

    void loadOpenglPointers();

    void clear(float red, float green, float blue, float alpha);

    void draw(const VertexArray& vertex_array, const Shader& shader, int count);

    void draw(const VertexArray& vertex_array, const Shader& shader,
              const IndexBuffer& index_buffer);

}; // namespace Renderer

#endif
