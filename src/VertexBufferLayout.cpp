#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout() : m_stride {0} {}

VertexBufferLayout::~VertexBufferLayout() {}

const std::vector<VertexBufferElement>& VertexBufferLayout::getElements() const
{
    return m_elements;
}

const unsigned int& VertexBufferLayout::getStride() const { return m_stride; }

template <typename T>
void VertexBufferLayout::Push(unsigned int count)
{
    static_assert(false);
}

template <>
void VertexBufferLayout::Push<float>(unsigned int count)
{
    m_elements.push_back({GL_FLOAT, count, GL_FALSE});
    m_stride += count * sizeof(GLfloat);
}

template <>
void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
    m_elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    m_stride += count * sizeof(GLuint);
}

template <>
void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
    m_elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
    m_stride += count * sizeof(GLbyte);
}
