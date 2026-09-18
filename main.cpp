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
    Renderer::initialise();

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
            glm::vec3(0.0F, 0.0F, 0.0F),     //
            glm::vec3(2.0F, 5.0F, -15.0F),   //
            glm::vec3(-1.5F, -2.2F, -2.5F),  //
            glm::vec3(-3.8F, -2.0F, -12.3F), //
            glm::vec3(2.4F, -0.4F, -3.5F),   //
            glm::vec3(-1.7F, 3.0F, -7.5F),   //
            glm::vec3(1.3F, -2.0F, -2.5F),   //
            glm::vec3(1.5F, 2.0F, -2.5F),    //
            glm::vec3(1.5F, 0.2F, -1.5F),    //
            glm::vec3(-1.3F, 1.0F, -1.5F)    //
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
            Renderer::clear(0.2F, 0.3F, 0.3F, 1.0F);

            glm::mat4 view {window.getViewMatrix()};
            cube_shader.SetUniformMatrix4fv("u_view", view);

            glm::mat4 projection {window.getProjectionMatrix()};
            cube_shader.SetUniformMatrix4fv("u_projection", projection);

            // draw squares
            constexpr int num_squares {10};
            for (unsigned int i = 0; i < num_squares; i++)
            {
                float deg {glm::radians(20.0F * static_cast<float>(i))};
                if (i % 3 == 0)
                {
                    deg = glm::radians(30.0F * current_frame);
                }

                glm::mat4 model {1.0F};
                model = glm::translate(model, cube_positions[i]);
                model = glm::rotate(model, deg, glm::vec3(1.0F, 0.3F, 0.5F));
                model = glm::scale(model, glm::vec3(0.8, 0.8, 0.8));
                cube_shader.SetUniformMatrix4fv("u_model", model);
                Renderer::draw(cube.getVertexArray(), cube_shader, 36);
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
