#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

#include <array>

class Triangle
{
  public:
    Triangle();
    ~Triangle() = default;

    const VertexArray& GetVertexArray() const { return m_vertexArray; };

  private:
    VertexBuffer m_vertexBuffer {};
    VertexBufferLayout m_vertexBufferLayout {};
    VertexArray m_vertexArray {};

    static constexpr std::array<float, 18> m_vertices {
        -1.0f, -1.0f, 0.0f, // left position
        1.0f,  0.0f,  0.0f, // left colour
        1.0f,  -1.0f, 0.0f, // right position
        0.0f,  1.0f,  0.0f, // right position
        0.0f,  1.0f,  0.0f, // top position
        0.0f,  0.0f,  1.0f  // top colour
    };
};

#endif
