#ifndef CUBE_H
#define CUBE_H

#include <array>

class Cube
{
  public:
    Cube(float size);
    ~Cube() = default;

    static std::array<float, 180> GetVertices(float size);
};

#endif
