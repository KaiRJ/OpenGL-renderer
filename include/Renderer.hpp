#ifndef RENDERER_H
#define RENDERER_H

#include <array>

class IndexBuffer;
class Shader;
class VertexArray;

namespace Renderer
{
    inline constexpr std::array<float, 4> default_colour {0.2F, 0.3F, 0.3F, 1.0F};

    void initialise();

    void clear(float red = default_colour[0], float green = default_colour[1],
               float blue = default_colour[2], float alpha = default_colour[3]);

    void draw(const VertexArray& vertex_array, const Shader& shader, int count);

    void draw(const VertexArray& vertex_array, const Shader& shader,
              const IndexBuffer& index_buffer);

}; // namespace Renderer

void loadOpenglPointers();

#endif
