#include "IndexBuffer.hpp"

IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &buffer_id); }

void IndexBuffer::bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id); }

void IndexBuffer::unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

int IndexBuffer::getCount() const { return count; }
