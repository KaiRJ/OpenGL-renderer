#include "Cube.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "VertexBuffer.hpp"
#include "Window.hpp"

#include <cassert>
#include <glm/gtc/matrix_transform.hpp>

int main()
{
    Window window {};
    Renderer renderer {};

    { // ensure objects are destroyed before glfwTerminate()
        Cube cube {};
        Shader cube_shader("shaders/cube.vert", "shaders/cube.frag");

        // when i create new texture it get automatically binds to first slot
        Texture container_texture {"../textures/container.jpg", GL_RGB};
        Texture face_texture {"../textures/awesomeface.png", GL_RGBA};
        container_texture.Bind(0);
        face_texture.Bind(1);
        cube_shader.SetUniform1i("u_texture0", 0);
        cube_shader.SetUniform1i("u_texture1", 1);

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

        // render loop
        float delta_time {0.0}; // time between current frame and last frame
        float last_frame {0.0}; // time of last frame
        while (!window.shouldClose())
        {
            float current_frame {static_cast<float>(glfwGetTime())};
            delta_time = current_frame - last_frame;
            last_frame = current_frame;

            window.processInput(delta_time);
            renderer.clear();

            glm::mat4 view {window.getViewMatrix()};
            cube_shader.SetUniformMatrix4fv("u_view", view);

            glm::mat4 projection {window.getProjectionMatrix()};
            cube_shader.SetUniformMatrix4fv("u_projection", projection);

            // draw squares
            for (unsigned int i = 0; i < 10; i++)
            {
                float deg {glm::radians(20.0f * i)};
                if (i % 3 == 0)
                    deg = glm::radians(30.0f * current_frame);

                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cube_positions[i]);
                model = glm::rotate(model, deg, glm::vec3(1.0f, 0.3f, 0.5f));
                model = glm::scale(model, glm::vec3(0.8, 0.8, 0.8));
                cube_shader.SetUniformMatrix4fv("u_model", model);
                renderer.draw(cube.getVertexArray(), cube_shader, 36);
            }

            // hot reload shaders
            // TODO need to track all objects in game and call reload, a shader vector
            // that is passed to window?
            if (window.wasKeyPressed(GLFW_KEY_R))
            {
                cube_shader.Reload();
            }

            window.swapBuffers();
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}
