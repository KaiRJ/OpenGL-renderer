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
#include <glm/gtc/matrix_transform.hpp>

#include <array>
#include <cassert>
#include <cmath>

int main()
{
    Window window {};
    initialiseDebugOutput();

    { // ensure objects are destroyed before glfwTerminate()
        // triangle setup
        Shader triangle_shader("shaders/triangle_shader.vert",
                               "shaders/triangle_shader.frag");

        constexpr float triangle_size {0.2};
        constexpr std::array vertices {
            -triangle_size, -triangle_size, 0.0f, // left position
            1.0f,           0.0f,           0.0f, // left colour
            triangle_size,  -triangle_size, 0.0f, // right position
            0.0f,           1.0f,           0.0f, // right position
            0.0f,           triangle_size,  0.0f, // top position
            0.0f,           0.0f,           1.0f  // top colour
        };
        VertexBuffer triangle_vb {vertices};

        VertexBufferLayout triangle_layout {};
        triangle_layout.Push<float>(3);
        triangle_layout.Push<float>(3);

        VertexArray triangle_va {};
        triangle_va.AddBuffer(triangle_vb, triangle_layout);

        // square setup
        Shader shader1("shaders/shader1.vert", "shaders/shader1.frag");

        constexpr float size {0.4};
        constexpr std::array positions {
            // positions                    // texture coords
            -size, -size, 0.0f, 0.0f, 0.0f, // bottom left
            size,  -size, 0.0f, 2.0f, 0.0f, // bottom right
            -size, size,  0.0f, 0.0f, 2.0f, // top left
            size,  size,  0.0f, 2.0f, 2.0f  // top right
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
        texture0.Bind(0);
        texture1.Bind(1);

        // Renderer object for drawing
        Renderer renderer {};

        // Matrices for square projection
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        // render loop
        while (!window.ShouldClose())
        {
            renderer.Clear();

            float time_s {static_cast<float>(glfwGetTime())};

            // draw triangle
            triangle_shader.Bind();
            glm::mat4 trans {glm::mat4(1.0f)};
            glm::vec3 offset {glm::vec3(0.5f, sin(time_s), 0.0f)};
            trans = glm::translate(trans, offset);
            triangle_shader.SetUniformMatrix4fv("u_transform", trans);
            renderer.Draw(triangle_va, triangle_shader, 3);

            // draw square
            shader1.Bind();
            shader1.SetUniformMatrix4fv("u_model", model);
            shader1.SetUniformMatrix4fv("u_view", view);
            shader1.SetUniformMatrix4fv("u_projection", projection);
            renderer.Draw(va1, shader1, ib);

            // hot reload shaders
            if (window.WasKeyPressed(GLFW_KEY_R))
            {
                shader1.Reload();
                triangle_shader.Reload();
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
