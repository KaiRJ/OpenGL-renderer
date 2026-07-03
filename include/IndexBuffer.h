#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

class IndexBuffer
{
  public:
    IndexBuffer(const unsigned int* indices, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    unsigned int GetCount() const;

  private:
    unsigned int m_bufferID;
    unsigned int m_count;
};

#endif
