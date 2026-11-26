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

    [[nodiscard]] const VertexArray& getVertexArray() const;

  private:
    VertexBuffer vertexBuffer;
    VertexBufferLayout vertexBufferLayout;
    VertexArray vertexArray;

    static constexpr std::array<float, 9> vertices {-0.5F, -0.5F, 0.0F, 0.5F, -0.5F,
                                                    0.0F,  0.0F,  0.5F, 0.0F};
};

#endif
