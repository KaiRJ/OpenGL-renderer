#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <cassert>
#include <cmath>
#include <iostream>
#include <string>

#include "Renderer.h"
#include "Shader.h"

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    if (!glfwInit())
    {
        std::cout << "Failed to start GLFW" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true); // slow!

    // glfw: window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // initialise debug output
    // -----------------------
    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr,
                              GL_TRUE);
    }

    // build and compile the shader programs
    // -------------------------------------
    Shader shaderProgram1("shaders/shader1.vert", "shaders/shader1.frag");
    Shader shaderProgram2("shaders/shader2.vert", "shaders/shader2.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float firstTriangle[] = {
        -0.9f,  -0.5f, 0.0f, // left
        -0.0f,  -0.5f, 0.0f, // right
        -0.45f, 0.5f,  0.0f, // top
    };
    float secondTriangle[] = {
        // position                     // colour
        0.0f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left
        0.9f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // right
        0.45f, 0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // top
    };

    // setup VAOs and VBOs
    unsigned int VAOs[2];
    glGenVertexArrays(2, VAOs);

    unsigned int VBOs[2];
    glGenBuffers(2, VBOs);

    // first triangle setup
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
    glEnableVertexAttribArray(0);

    // second triangle setup
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (const void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    double prev_s {glfwGetTime()};
    double title_countdown_s {};
    while (!glfwWindowShouldClose(window))
    {
        double curr_s {glfwGetTime()};

        // frame rate
        // ----------
        double elapsed_s {curr_s - prev_s};
        prev_s = curr_s;

        title_countdown_s -= elapsed_s;
        if (title_countdown_s <= 0.0 && elapsed_s > 0.0)
        {
            double fps {1.0 / elapsed_s};
            std::string str {"FPS " + std::to_string(fps)};
            glfwSetWindowTitle(window, str.c_str());
            title_countdown_s = 0.5;
        }

        // input
        // -----
        processInput(window);

        // clear colour buffer
        // -------------------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw first triangle
        // -------------------
        // activate correct shader
        shaderProgram1.use();

        // update uniform time
        int time_loc {glGetUniformLocation(shaderProgram1.ID, "u_time_s")};
        assert(time_loc != -1);
        glUniform1f(time_loc, curr_s);

        // render the triangle
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // draw second triangle
        // --------------------
        // activate correct shader
        shaderProgram2.use();

        // update uniform time
        time_loc = glGetUniformLocation(shaderProgram2.ID, "u_time_s");
        assert(time_loc != -1);
        glUniform1f(time_loc, curr_s);

        // render the triangle
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // swap buffers and poll IO events
        // -------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // de-allocate all resources
    // -------------------------
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);

    // glfw: terminate
    // ---------------
    glfwTerminate();
    return 0;
}

// whenever the window size changed this callback function executes
// ----------------------------------------------------------------
static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// process all input accordingly
// -----------------------------
static void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
