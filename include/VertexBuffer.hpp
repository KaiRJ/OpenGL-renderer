#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <glad/glad.h>

#include <array>

class VertexBuffer
{
  public:
    VertexBuffer() = default;
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

    template <typename T, std::size_t N>
    void AddData(std::array<T, N> data);

  private:
    unsigned int m_bufferID;
};

template <typename T, std::size_t N>
void VertexBuffer::AddData(std::array<T, N> data)
{
    glGenBuffers(1, &m_bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data.data(), GL_STATIC_DRAW);
}

#endif
