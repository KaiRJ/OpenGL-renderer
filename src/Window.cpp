#include "Window.h"

#include <glad/glad.h>
#include <stdexcept>

static void initialise_glfw();
static void load_opengl_pointers();
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Window::Window()
{
    initialise_glfw();
    CreateWindow();
    load_opengl_pointers();
}

void Window::CreateWindow()
{
    window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void Window::ProcessInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

bool Window::ShouldClose() { return glfwWindowShouldClose(window); }

void Window::SwapBuffers() { glfwSwapBuffers(window); }

// initialize and configure glfw
// -----------------------------
static void initialise_glfw()
{
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to start GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true); // slow!
}

// load all OpenGL function pointers from glad
// -------------------------------------------
static void load_opengl_pointers()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }
}

// whenever the window size changed this callback function executes
// ----------------------------------------------------------------
static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
