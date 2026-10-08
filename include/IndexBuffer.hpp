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

    void bind() const;
    static void unbind();

    [[nodiscard]] int getCount() const;

  private:
    unsigned int buffer_id;
    int count;
};

template <std::size_t N>
IndexBuffer::IndexBuffer(const std::array<unsigned int, N>& indices) : count {N}
{
    glGenBuffers(1, &buffer_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(),
                 GL_STATIC_DRAW);
}
#endif
