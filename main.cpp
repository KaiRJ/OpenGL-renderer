#include "Debug.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Window.h"

#include <cassert>
#include <cmath>
#include <glad/glad.h>

int main()
{
    Window window {};
    initialiseDebugOutput();

    { // ensure objects are destroyed before glfwTerminate()
        // shader programs setup
        Shader shaderProgram1("shaders/shader1.vert", "shaders/shader1.frag");
        Shader shaderProgram2("shaders/shader2.vert", "shaders/shader2.frag");

        // first triangle setup
        float positions[] = {
            -0.9f,  -0.5f, 0.0f, // left
            -0.0f,  -0.5f, 0.0f, // right
            -0.45f, 0.5f,  0.0f, // top
        };
        VertexArray va1 {};
        VertexBuffer vb1 {positions, sizeof(positions)};
        VertexBufferLayout layout1 {};
        layout1.Push<float>(3);
        va1.AddBuffer(vb1, layout1);

        // second triangle setup
        float positionsAndColours[] = {
            // position                     // colour
            0.0f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left
            0.9f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // right
            0.45f, 0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // top
        };
        VertexArray va2 {};
        VertexBuffer vb2 {positionsAndColours, sizeof(positionsAndColours)};
        VertexBufferLayout layout2 {};
        layout2.Push<float>(3);
        layout2.Push<float>(3);
        va2.AddBuffer(vb2, layout2);

        // render loop
        while (!window.ShouldClose())
        {
            window.ProcessInput();
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // draw first triangle
            // -------------------
            shaderProgram1.use();
            int time_loc {glGetUniformLocation(shaderProgram1.ID, "u_time_s")};
            assert(time_loc != -1);
            glUniform1f(time_loc, glfwGetTime());

            // render the triangle
            va1.Bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);

            // draw second triangle
            // --------------------
            shaderProgram2.use();
            time_loc = glGetUniformLocation(shaderProgram2.ID, "u_time_s");
            assert(time_loc != -1);
            glUniform1f(time_loc, glfwGetTime());

            // render the triangle
            va2.Bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);

            window.SwapBuffers();
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}
