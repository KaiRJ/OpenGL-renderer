#include "VertexBuffer.hpp"

VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &m_bufferID); }

void VertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_bufferID); }

void VertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
