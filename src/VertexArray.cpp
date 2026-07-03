#include "VertexArray.h"

VertexArray::VertexArray() { glGenVertexArrays(1, &m_bufferID); }

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &m_bufferID); }

void VertexArray::AddBuffer(const VertexBuffer& vb,
                            const VertexBufferLayout& layout) const
{
    Bind();
    vb.Bind();
    uintptr_t offset {0};
    const auto& elements {layout.getElements()};
    for (auto i {0}; i < std::size(elements); ++i)
    {
        const auto& element {elements[i]};
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalised,
                              layout.getStride(), reinterpret_cast<const void*>(offset));
        offset += element.count * sizeof(element.type);
    }
}

void VertexArray::Bind() const { glBindVertexArray(m_bufferID); }

void VertexArray::Unbind() const { glBindVertexArray(0); }
