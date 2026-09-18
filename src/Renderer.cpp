#include "Renderer.hpp"
#include "Debug.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stdexcept>

namespace Renderer
{
    void initialise()
    {
        loadOpenglPointers();
        Debug::initialiseDebugOutput();
        glEnable(GL_DEPTH_TEST);
    }

    void loadOpenglPointers()
    {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            throw std::runtime_error("Failed to initialize GLAD");
        }
    }

    void clear(float red, float green, float blue, float alpha)
    {
        glClearColor(red, green, blue, alpha);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void draw(const VertexArray& vertex_array, const Shader& shader, int count)
    {
        vertex_array.Bind();
        shader.Bind();
        glDrawArrays(GL_TRIANGLES, 0, count);
    }

    void draw(const VertexArray& vertex_array, const Shader& shader,
              const IndexBuffer& index_buffer)
    {
        vertex_array.Bind();
        shader.Bind();
        index_buffer.Bind();
        glDrawElements(GL_TRIANGLES, index_buffer.GetCount(), GL_UNSIGNED_INT, nullptr);
    }

} // namespace Renderer
