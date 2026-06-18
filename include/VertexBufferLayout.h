#ifndef VERTEX_ARRAY_LAYOUT_H
#define VERTEX_ARRAY_LAYOUT_H

#include "Debug.h"
#include <glad/glad.h>
#include <vector>

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned int normalised;
};

class VertexBufferLayout
{
  public:
    VertexBufferLayout();
    ~VertexBufferLayout();

    const std::vector<VertexBufferElement>& getElements() const;
    const unsigned int& getStride() const;

    template <typename T>
    void Push(unsigned int count);

  private:
    std::vector<VertexBufferElement> m_Elements {};
    unsigned int m_Stride {};
};

#endif
