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

    const VertexArray& getVertexArray() const;

  private:
    VertexBuffer vertexBuffer {};
    VertexBufferLayout vertexBufferLayout {};
    VertexArray vertexArray {};

    static constexpr std::array<float, 180> vertices {-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, //
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
