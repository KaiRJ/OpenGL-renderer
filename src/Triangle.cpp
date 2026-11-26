#include "Triangle.hpp"

Triangle::Triangle()
{
    vertexBuffer.AddData(vertices);
    vertexBufferLayout.Push<float>(3);
    vertexArray.AddBuffer(vertexBuffer, vertexBufferLayout);
}

const VertexArray& Triangle::getVertexArray() const { return vertexArray; };
