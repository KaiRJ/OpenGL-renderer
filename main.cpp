#include "Debug.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Window.h"

#include <glad/glad.h>

#include <cassert>
#include <cmath>

namespace
{
    constexpr float positions[] = {
        -0.9f, -0.5f, 0.0f, // bottom left
        -0.0f, -0.5f, 0.0f, // bottom right
        -0.9f, 0.5f,  0.0f, // top left
        -0.0f, 0.5f,  0.0f, // top right
    };

    constexpr unsigned int indices[] = {
        0, 1, 3, // lower half
        0, 2, 3  // upper second
    };

    constexpr float positionsAndColours[] = {
        // position                     // colour
        0.0f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left
        0.9f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // right
        0.45f, 0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // top
    };

} // namespace

int main()
{
    Window window {};
    initialiseDebugOutput();

    { // ensure objects are destroyed before glfwTerminate()
        // shader programs setup
        const char* vertexShader1Path {"shaders/shader1.vert"};
        const char* fragmentShader1Path {"shaders/shader1.frag"};
        Shader shader1(vertexShader1Path, fragmentShader1Path);

        const char* vertexShader2Path {"shaders/shader2.vert"};
        const char* fragmentShader2Path {"shaders/shader2.frag"};
        Shader shader2(vertexShader2Path, fragmentShader2Path);

        // square setup
        VertexBuffer vb1 {positions, sizeof(positions)};
        IndexBuffer ib {indices, 6};

        VertexBufferLayout layout1 {};
        layout1.Push<float>(3);

        VertexArray va1 {};
        va1.AddBuffer(vb1, layout1);

        // triangle setup
        VertexBuffer vb2 {positionsAndColours, sizeof(positionsAndColours)};

        VertexBufferLayout layout2 {};
        layout2.Push<float>(3);
        layout2.Push<float>(3);

        VertexArray va2 {};
        va2.AddBuffer(vb2, layout2);

        // Renderer object for drawing
        Renderer renderer {};

        // render loop
        while (!window.ShouldClose())
        {
            renderer.Clear();

            // draw square
            shader1.Bind();
            shader1.SetUniform1f("u_time_s", glfwGetTime());
            // renderer.Draw(va1, shader1, 3);
            renderer.Draw(va1, shader1, ib);

            // draw triangle
            shader2.Bind();
            shader2.SetUniform1f("u_time_s", glfwGetTime());
            shader2.SetUniform1f("u_x_offset", 0.2);
            renderer.Draw(va2, shader2, 3);

            // hot reload shaders
            if (window.WasKeyPressed(GLFW_KEY_R))
            {
                shader1.Reload(vertexShader1Path, fragmentShader1Path);
                shader2.Reload(vertexShader2Path, fragmentShader2Path);
            }

            // swap buffers and handle input
            window.ProcessInput();
            window.SwapBuffers();
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}
