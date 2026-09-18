#include "Window.hpp"
#include "Camera.hpp"

#include <glad/glad.h>
#include <stdexcept>

static void initialiseGlfw();
static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
static void mouseCallback(GLFWwindow* window, double x_pos, double y_pos);
static void scrollCallback(GLFWwindow* window, double x_offset, double y_offset);

Window::Window()
{
    initialiseGlfw();
    createWindow();
}

Window::~Window() { glfwDestroyWindow(window); }

Camera& Window::getCamera() { return camera; }

glm::mat4 Window::getViewMatrix() const { return camera.getViewMatrix(); };

glm::mat4 Window::getProjectionMatrix() const
{
    float aspect {static_cast<float>(width) / static_cast<float>(height)};
    return glm::perspective(glm::radians(camera.getZoom()), aspect, 0.1F, 100.0F);
};

void Window::createWindow()
{
    window = glfwCreateWindow(width, height, "OpenGL Renderer", nullptr, nullptr);
    if (window == nullptr)
    {
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);
}

bool Window::wasKeyPressed(int key) const
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}

void Window::processInput(float delta_time)
{
    if (wasKeyPressed(GLFW_KEY_W))
    {
        camera.handleKeyboard(Camera::forward, delta_time);
    }

    if (wasKeyPressed(GLFW_KEY_S))
    {
        camera.handleKeyboard(Camera::backward, delta_time);
    }

    if (wasKeyPressed(GLFW_KEY_A))
    {
        camera.handleKeyboard(Camera::leftward, delta_time);
    }

    if (wasKeyPressed(GLFW_KEY_D))
    {
        camera.handleKeyboard(Camera::rightward, delta_time);
    }

    if (wasKeyPressed(GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(window, true);
    }
}

bool Window::shouldClose() const { return glfwWindowShouldClose(window); }

void Window::swapBuffers() const { glfwSwapBuffers(window); }

static void initialiseGlfw()
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

static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static void mouseCallback(GLFWwindow* window, double x_pos, double y_pos)
{
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    self->getCamera().handleMouseCallback(x_pos, y_pos);
}

static void scrollCallback(GLFWwindow* window, double x_offset, double y_offset)
{
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    self->getCamera().handleScrollCallback(x_offset, y_offset);
}
