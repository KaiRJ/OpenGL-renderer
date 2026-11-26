#include "Triangles.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "Triangle.hpp"

namespace Test
{
    void Triangles::onRender()
    {
        Triangle triangle;
        Shader shader {"shaders/triangle.vert", "shaders/triangle.frag"};
        Renderer::draw(triangle.getVertexArray(), shader, 3);
    }
} // namespace Test
