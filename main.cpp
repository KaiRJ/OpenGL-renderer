#include "Debug.hpp"
#include "IndexBuffer.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "Window.hpp"

#include <glad/glad.h>

#include <array>
#include <cassert>
#include <cmath>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

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
            -0.0f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
            -0.9f, 0.5f,  0.0f, 0.0f, 1.0f, // top left
            -0.0f, 0.5f,  0.0f, 1.0f, 1.0f  // top right
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

        // Texture code (to be moved to own class)
        stbi_set_flip_vertically_on_load(true);

        unsigned int texture1;
        glGenTextures(1, &texture1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load and generate the texture
        int width, height, nrChannels;
        unsigned char* data =
            stbi_load("../textures/container.jpg", &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                         GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);

        // Texture code (to be moved to own class)
        unsigned int texture2;
        glGenTextures(1, &texture2);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load and generate the texture
        data = stbi_load("../textures/awesomeface.png", &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                         GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);

        shader1.Bind();
        shader1.SetUniform1i("u_texture1", 0);
        shader1.SetUniform1i("u_texture2", 1);

        // render loop
        while (!window.ShouldClose())
        {
            renderer.Clear();

            // draw square
            shader1.Bind();
            shader1.SetUniform1f("u_time_s", glfwGetTime());
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture1);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture2);
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
