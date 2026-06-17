#include "Debug.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "Window.h"

#include <cassert>
#include <cmath>
#include <glad/glad.h>

int main()
{
    Window window {};

    initialiseDebugOutput();

    // build and compile the shader programs
    // -------------------------------------
    Shader shaderProgram1("shaders/shader1.vert", "shaders/shader1.frag");
    Shader shaderProgram2("shaders/shader2.vert", "shaders/shader2.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    unsigned int VAOs[2];
    glGenVertexArrays(2, VAOs);

    // first triangle setup
    glBindVertexArray(VAOs[0]);
    float positions[] = {
        -0.9f,  -0.5f, 0.0f, // left
        -0.0f,  -0.5f, 0.0f, // right
        -0.45f, 0.5f,  0.0f, // top
    };
    auto solidTriangle = new VertexBuffer(positions, sizeof(positions));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
    glEnableVertexAttribArray(0);

    // second triangle setup
    glBindVertexArray(VAOs[1]);
    float positionsAndColours[] = {
        // position                     // colour
        0.0f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left
        0.9f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // right
        0.45f, 0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // top
    };
    auto movingTriangle =
        new VertexBuffer(positionsAndColours, sizeof(positionsAndColours));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (const void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // render loop
    while (!window.ShouldClose())
    {
        window.ProcessInput();

        // clear colour buffer
        // -------------------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw first triangle
        // -------------------
        shaderProgram1.use();

        // update uniform time
        int time_loc {glGetUniformLocation(shaderProgram1.ID, "u_time_s")};
        assert(time_loc != -1);
        glUniform1f(time_loc, glfwGetTime());

        // render the triangle
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // draw second triangle
        // --------------------
        shaderProgram2.use();

        // update uniform time
        time_loc = glGetUniformLocation(shaderProgram2.ID, "u_time_s");
        assert(time_loc != -1);
        glUniform1f(time_loc, glfwGetTime());

        // render the triangle
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.SwapBuffers();
        glfwPollEvents();
    }

    delete solidTriangle;
    delete movingTriangle;
    glDeleteVertexArrays(2, VAOs);
    glfwTerminate();

    return 0;
}
