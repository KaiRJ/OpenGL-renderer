#include "Debug.hpp"
#include "IndexBuffer.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "Window.hpp"

#include <glad/glad.h>

#include <array>
#include <cassert>
#include <cmath>
#include <iostream>

int main()
{
    Window window {};
    initialiseDebugOutput();

    { // ensure objects are destroyed before glfwTerminate()
        // shader programs setup
        Shader shader1("shaders/shader1.vert", "shaders/shader1.frag");
        Shader shader2("shaders/shader2.vert", "shaders/shader2.frag");

        // square setup
        constexpr std::array positions {
            // positions                    // texture coords
            -0.9f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
            -0.0f, -0.5f, 0.0f, 2.0f, 0.0f, // bottom right
            -0.9f, 0.5f,  0.0f, 0.0f, 2.0f, // top left
            -0.0f, 0.5f,  0.0f, 2.0f, 2.0f  // top right
        };
        VertexBuffer vb1 {positions};

        constexpr std::array indices {
            0u, 1u, 3u, // lower half
            0u, 2u, 3u  // upper second
        };
        IndexBuffer ib {indices};

        VertexBufferLayout layout1 {};
        layout1.Push<float>(3);
        layout1.Push<float>(2);

        VertexArray va1 {};
        va1.AddBuffer(vb1, layout1);

        // order of code is important as calls to glbindTexure will bind that texture to
        // the currently active texture unit.
        Texture texture0 {"../textures/container.jpg", GL_RGB};
        Texture texture1 {"../textures/awesomeface.png", GL_RGBA};
        shader1.Bind();
        shader1.SetUniform1i("u_texture1", 0);
        shader1.SetUniform1i("u_texture2", 1);
        texture0.Bind(GL_TEXTURE0);
        texture1.Bind(GL_TEXTURE1);

        // triangle setup
        constexpr std::array vertices {
            // position                     // colour
            0.0f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left
            0.9f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // right
            0.45f, 0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // top
        };
        VertexBuffer vb2 {vertices};

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
            renderer.Draw(va1, shader1, ib);

            // draw triangle
            shader2.Bind();
            shader2.SetUniform1f("u_time_s", glfwGetTime());
            shader2.SetUniform1f("u_x_offset", 0.2);
            renderer.Draw(va2, shader2, 3);

            // hot reload shaders
            if (window.WasKeyPressed(GLFW_KEY_R))
            {
                shader1.Reload();
                shader2.Reload();
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
