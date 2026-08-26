#ifndef CUBE_H
#define CUBE_H

#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

#include <array>

class Cube
{
  public:
    Cube();
    ~Cube() = default;

    const VertexArray& GetVertexArray() const { return m_vertexArray; };

  private:
    VertexBuffer m_vertexBuffer {};
    VertexBufferLayout m_vertexBufferLayout {};
    VertexArray m_vertexArray {};

    static constexpr std::array<float, 180> m_vertices {
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, //
        1.0f,  -1.0f, -1.0f, 1.0f, 0.0f, //
        1.0f,  1.0f,  -1.0f, 1.0f, 1.0f, //
        1.0f,  1.0f,  -1.0f, 1.0f, 1.0f, //
        -1.0f, 1.0f,  -1.0f, 0.0f, 1.0f, //
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, //

        -1.0f, -1.0f, 1.0f,  0.0f, 0.0f, //
        1.0f,  -1.0f, 1.0f,  1.0f, 0.0f, //
        1.0f,  1.0f,  1.0f,  1.0f, 1.0f, //
        1.0f,  1.0f,  1.0f,  1.0f, 1.0f, //
        -1.0f, 1.0f,  1.0f,  0.0f, 1.0f, //
        -1.0f, -1.0f, 1.0f,  0.0f, 0.0f, //

        -1.0f, 1.0f,  1.0f,  1.0f, 0.0f, //
        -1.0f, 1.0f,  -1.0f, 1.0f, 1.0f, //
        -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, //
        -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, //
        -1.0f, -1.0f, 1.0f,  0.0f, 0.0f, //
        -1.0f, 1.0f,  1.0f,  1.0f, 0.0f, //

        1.0f,  1.0f,  1.0f,  1.0f, 0.0f, //
        1.0f,  1.0f,  -1.0f, 1.0f, 1.0f, //
        1.0f,  -1.0f, -1.0f, 0.0f, 1.0f, //
        1.0f,  -1.0f, -1.0f, 0.0f, 1.0f, //
        1.0f,  -1.0f, 1.0f,  0.0f, 0.0f, //
        1.0f,  1.0f,  1.0f,  1.0f, 0.0f, //

        -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, //
        1.0f,  -1.0f, -1.0f, 1.0f, 1.0f, //
        1.0f,  -1.0f, 1.0f,  1.0f, 0.0f, //
        1.0f,  -1.0f, 1.0f,  1.0f, 0.0f, //
        -1.0f, -1.0f, 1.0f,  0.0f, 0.0f, //
        -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, //

        -1.0f, 1.0f,  -1.0f, 0.0f, 1.0f, //
        1.0f,  1.0f,  -1.0f, 1.0f, 1.0f, //
        1.0f,  1.0f,  1.0f,  1.0f, 0.0f, //
        1.0f,  1.0f,  1.0f,  1.0f, 0.0f, //
        -1.0f, 1.0f,  1.0f,  0.0f, 0.0f, //
        -1.0f, 1.0f,  -1.0f, 0.0f, 1.0f};
};

#endif
