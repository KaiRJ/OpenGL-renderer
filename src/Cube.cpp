#include "Cube.hpp"

Cube::Cube()
{
    vertexBuffer.AddData(vertices);
    vertexBufferLayout.Push<float>(3);
    vertexBufferLayout.Push<float>(2);

    vertexArray.AddBuffer(vertexBuffer, vertexBufferLayout);
}

const VertexArray& Cube::getVertexArray() const { return vertexArray; };
