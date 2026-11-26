#include "Cube.hpp"

Cube::Cube()
{
    vertex_buffer.AddData(vertices);
    vertex_buffer_layout.Push<float>(3);
    vertex_buffer_layout.Push<float>(2);
    vertex_array.AddBuffer(vertex_buffer, vertex_buffer_layout);
}

const VertexArray& Cube::getVertexArray() const { return vertex_array; };
