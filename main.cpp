#include "Cube.hpp"
#include "Debug.hpp"
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
        constexpr std::array triangle_vertices {
            -triangle_size, -triangle_size, 0.0f, // left position
            1.0f,           0.0f,           0.0f, // left colour
            triangle_size,  -triangle_size, 0.0f, // right position
            0.0f,           1.0f,           0.0f, // right position
            0.0f,           triangle_size,  0.0f, // top position
            0.0f,           0.0f,           1.0f  // top colour
        };
        VertexBuffer triangle_vb {triangle_vertices};

        VertexBufferLayout triangle_layout {};
        triangle_layout.Push<float>(3);
        triangle_layout.Push<float>(3);

        VertexArray triangle_va {};
        triangle_va.AddBuffer(triangle_vb, triangle_layout);

        // square setup
        Shader cube_shader("shaders/cube_shader.vert", "shaders/cube_shader.frag");

        std::array cube_vertices {Cube::GetVertices(0.5)};
        VertexBuffer cube_vb {cube_vertices};

        VertexBufferLayout cube_layout {};
        cube_layout.Push<float>(3);
        cube_layout.Push<float>(2);

        VertexArray cube_va {};
        cube_va.AddBuffer(cube_vb, cube_layout);

        // order of code is important as calls to glbindTexure will bind that texture to
        // the currently active texture unit.
        Texture texture0 {"../textures/container.jpg", GL_RGB};
        Texture texture1 {"../textures/awesomeface.png", GL_RGBA};
        cube_shader.SetUniform1i("u_texture1", 0);
        cube_shader.SetUniform1i("u_texture2", 1);
        texture0.Bind(0);
        texture1.Bind(1);

        // matrices for cube projection
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        glm::mat4 projection {
            glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f)};

        // positions for all cubes
        constexpr glm::vec3 cube_positions[] = {
            glm::vec3(0.0f, 0.0f, 0.0f),     //
            glm::vec3(2.0f, 5.0f, -15.0f),   //
            glm::vec3(-1.5f, -2.2f, -2.5f),  //
            glm::vec3(-3.8f, -2.0f, -12.3f), //
            glm::vec3(2.4f, -0.4f, -3.5f),   //
            glm::vec3(-1.7f, 3.0f, -7.5f),   //
            glm::vec3(1.3f, -2.0f, -2.5f),   //
            glm::vec3(1.5f, 2.0f, -2.5f),    //
            glm::vec3(1.5f, 0.2f, -1.5f),    //
            glm::vec3(-1.3f, 1.0f, -1.5f)    //
        };

        // Renderer object for drawing
        Renderer renderer {};

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

            // apply matrices for square projection
            cube_shader.SetUniformMatrix4fv("u_view", view);
            cube_shader.SetUniformMatrix4fv("u_projection", projection);

            // draw squares
            for (unsigned int i = 0; i < 10; i++)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cube_positions[i]);
                float angle = 20.0f * i;
                model =
                    glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                cube_shader.SetUniformMatrix4fv("u_model", model);

                renderer.Draw(cube_va, cube_shader, 36);
            }

            // hot reload shaders
            if (window.WasKeyPressed(GLFW_KEY_R))
            {
                cube_shader.Reload();
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
