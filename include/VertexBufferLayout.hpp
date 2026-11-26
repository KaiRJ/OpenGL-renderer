#ifndef VERTEX_ARRAY_LAYOUT_H
#define VERTEX_ARRAY_LAYOUT_H

#include <glad/glad.h>
#include <vector>

struct VertexBufferElement
{
    unsigned int type {};
    unsigned int count {};
    unsigned int normalised {};
};

class VertexBufferLayout
{
  public:
    VertexBufferLayout() = default;
    ~VertexBufferLayout() = default;

    [[nodiscard]] const std::vector<VertexBufferElement>& getElements() const;
    [[nodiscard]] const unsigned int& getStride() const;

    template <typename T>
    void Push(unsigned int count);

  private:
    std::vector<VertexBufferElement> elements;
    unsigned int stride {0};
};

#endif
