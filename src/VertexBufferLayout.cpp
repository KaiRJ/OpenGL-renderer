#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout() : m_Stride {0} {}

VertexBufferLayout::~VertexBufferLayout() {}

const std::vector<VertexBufferElement>& VertexBufferLayout::getElements() const
{
    return m_Elements;
}

const unsigned int& VertexBufferLayout::getStride() const { return m_Stride; }

template <typename T>
void VertexBufferLayout::Push(unsigned int count)
{
    static_assert(false);
}

template <>
void VertexBufferLayout::Push<float>(unsigned int count)
{
    m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
    m_Stride += count * sizeof(GLfloat);
}

template <>
void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
    m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    m_Stride += count * sizeof(GLuint);
}

template <>
void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
    m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
    m_Stride += count * sizeof(GLbyte);
}
