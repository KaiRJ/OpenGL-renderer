#include "VertexBuffer.h"

#include <glad/glad.h>

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    glGenBuffers(1, &m_bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &m_bufferID); }

void VertexBuffer::Bind() const { glBindVertexArray(m_bufferID); }

void VertexBuffer::Unbind() const { glBindVertexArray(0); }
