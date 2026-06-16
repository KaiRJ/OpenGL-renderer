#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

class VertexBuffer
{
  private:
    unsigned int m_rendererID;

  public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind();
    void Unbind();
};

#endif
