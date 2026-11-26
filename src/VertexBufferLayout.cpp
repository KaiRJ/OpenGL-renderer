#include "VertexBufferLayout.hpp"

const std::vector<VertexBufferElement>& VertexBufferLayout::getElements() const
{
    return elements;
}

const unsigned int& VertexBufferLayout::getStride() const { return stride; }

template <typename T>
void VertexBufferLayout::Push(unsigned int count)
{
    static_assert(false);
}

template <>
void VertexBufferLayout::Push<float>(unsigned int count)
{
    elements.push_back({GL_FLOAT, count, GL_FALSE});
    stride += count * sizeof(GLfloat);
}

template <>
void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
    elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    stride += count * sizeof(GLuint);
}

template <>
void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
    elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
    stride += count * sizeof(GLbyte);
}
