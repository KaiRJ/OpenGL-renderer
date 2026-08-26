#include "Triangle.hpp"

Triangle::Triangle()
{
    m_vertexBuffer.AddData(m_vertices);
    m_vertexBufferLayout.Push<float>(3);
    m_vertexBufferLayout.Push<float>(3);

    m_vertexArray.AddBuffer(m_vertexBuffer, m_vertexBufferLayout);
}
