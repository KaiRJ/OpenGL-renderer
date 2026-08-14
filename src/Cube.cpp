#include "Cube.hpp"

#include <array>

std::array<float, 180> Cube::GetVertices(float size)
{

    std::array vertices {-size, -size, -size, 0.0f, 0.0f, //
                         size,  -size, -size, 1.0f, 0.0f, //
                         size,  size,  -size, 1.0f, 1.0f, //
                         size,  size,  -size, 1.0f, 1.0f, //
                         -size, size,  -size, 0.0f, 1.0f, //
                         -size, -size, -size, 0.0f, 0.0f, //

                         -size, -size, size,  0.0f, 0.0f, //
                         size,  -size, size,  1.0f, 0.0f, //
                         size,  size,  size,  1.0f, 1.0f, //
                         size,  size,  size,  1.0f, 1.0f, //
                         -size, size,  size,  0.0f, 1.0f, //
                         -size, -size, size,  0.0f, 0.0f, //

                         -size, size,  size,  1.0f, 0.0f, //
                         -size, size,  -size, 1.0f, 1.0f, //
                         -size, -size, -size, 0.0f, 1.0f, //
                         -size, -size, -size, 0.0f, 1.0f, //
                         -size, -size, size,  0.0f, 0.0f, //
                         -size, size,  size,  1.0f, 0.0f, //

                         size,  size,  size,  1.0f, 0.0f, //
                         size,  size,  -size, 1.0f, 1.0f, //
                         size,  -size, -size, 0.0f, 1.0f, //
                         size,  -size, -size, 0.0f, 1.0f, //
                         size,  -size, size,  0.0f, 0.0f, //
                         size,  size,  size,  1.0f, 0.0f, //

                         -size, -size, -size, 0.0f, 1.0f, //
                         size,  -size, -size, 1.0f, 1.0f, //
                         size,  -size, size,  1.0f, 0.0f, //
                         size,  -size, size,  1.0f, 0.0f, //
                         -size, -size, size,  0.0f, 0.0f, //
                         -size, -size, -size, 0.0f, 1.0f, //

                         -size, size,  -size, 0.0f, 1.0f, //
                         size,  size,  -size, 1.0f, 1.0f, //
                         size,  size,  size,  1.0f, 0.0f, //
                         size,  size,  size,  1.0f, 0.0f, //
                         -size, size,  size,  0.0f, 0.0f, //
                         -size, size,  -size, 0.0f, 1.0f};

    return vertices;
}
