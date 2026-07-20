#include "IndexBuffer.hpp"

IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &m_bufferID); }

void IndexBuffer::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID); }

void IndexBuffer::Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

unsigned int IndexBuffer::GetCount() const { return m_count; }
