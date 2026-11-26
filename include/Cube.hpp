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

    [[nodiscard]] const VertexArray& getVertexArray() const;

  private:
    VertexBuffer vertex_buffer;
    VertexBufferLayout vertex_buffer_layout;
    VertexArray vertex_array;

    static constexpr std::array<float, 180> vertices {-1.0F, -1.0F, -1.0F, 0.0F, 0.0F, //
                                                      1.0F,  -1.0F, -1.0F, 1.0F, 0.0F, //
                                                      1.0F,  1.0F,  -1.0F, 1.0F, 1.0F, //
                                                      1.0F,  1.0F,  -1.0F, 1.0F, 1.0F, //
                                                      -1.0F, 1.0F,  -1.0F, 0.0F, 1.0F, //
                                                      -1.0F, -1.0F, -1.0F, 0.0F, 0.0F, //

                                                      -1.0F, -1.0F, 1.0F,  0.0F, 0.0F, //
                                                      1.0F,  -1.0F, 1.0F,  1.0F, 0.0F, //
                                                      1.0F,  1.0F,  1.0F,  1.0F, 1.0F, //
                                                      1.0F,  1.0F,  1.0F,  1.0F, 1.0F, //
                                                      -1.0F, 1.0F,  1.0F,  0.0F, 1.0F, //
                                                      -1.0F, -1.0F, 1.0F,  0.0F, 0.0F, //

                                                      -1.0F, 1.0F,  1.0F,  1.0F, 0.0F, //
                                                      -1.0F, 1.0F,  -1.0F, 1.0F, 1.0F, //
                                                      -1.0F, -1.0F, -1.0F, 0.0F, 1.0F, //
                                                      -1.0F, -1.0F, -1.0F, 0.0F, 1.0F, //
                                                      -1.0F, -1.0F, 1.0F,  0.0F, 0.0F, //
                                                      -1.0F, 1.0F,  1.0F,  1.0F, 0.0F, //

                                                      1.0F,  1.0F,  1.0F,  1.0F, 0.0F, //
                                                      1.0F,  1.0F,  -1.0F, 1.0F, 1.0F, //
                                                      1.0F,  -1.0F, -1.0F, 0.0F, 1.0F, //
                                                      1.0F,  -1.0F, -1.0F, 0.0F, 1.0F, //
                                                      1.0F,  -1.0F, 1.0F,  0.0F, 0.0F, //
                                                      1.0F,  1.0F,  1.0F,  1.0F, 0.0F, //

                                                      -1.0F, -1.0F, -1.0F, 0.0F, 1.0F, //
                                                      1.0F,  -1.0F, -1.0F, 1.0F, 1.0F, //
                                                      1.0F,  -1.0F, 1.0F,  1.0F, 0.0F, //
                                                      1.0F,  -1.0F, 1.0F,  1.0F, 0.0F, //
                                                      -1.0F, -1.0F, 1.0F,  0.0F, 0.0F, //
                                                      -1.0F, -1.0F, -1.0F, 0.0F, 1.0F, //

                                                      -1.0F, 1.0F,  -1.0F, 0.0F, 1.0F, //
                                                      1.0F,  1.0F,  -1.0F, 1.0F, 1.0F, //
                                                      1.0F,  1.0F,  1.0F,  1.0F, 0.0F, //
                                                      1.0F,  1.0F,  1.0F,  1.0F, 0.0F, //
                                                      -1.0F, 1.0F,  1.0F,  0.0F, 0.0F, //
                                                      -1.0F, 1.0F,  -1.0F, 0.0F, 1.0F};
};

#endif
