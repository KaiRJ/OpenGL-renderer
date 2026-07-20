#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <glad/glad.h>

#include <array>

class IndexBuffer
{
  public:
    template <std::size_t N>
    IndexBuffer(const std::array<unsigned int, N>& indices);

    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    unsigned int GetCount() const;

  private:
    unsigned int m_bufferID;
    unsigned int m_count;
};

template <std::size_t N>
IndexBuffer::IndexBuffer(const std::array<unsigned int, N>& indices) : m_count(N)
{
    glGenBuffers(1, &m_bufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(),
                 GL_STATIC_DRAW);
}
#endif
