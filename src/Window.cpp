#include "Window.hpp"
#include "Camera.hpp"
#include "Gui.hpp"

#include "GLFW/glfw3.h"
#include <glad/glad.h>
#include <stdexcept>

Window::Window()
{
    initialiseGlfw();
    createWindow();
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);
}

Window::~Window() { glfwDestroyWindow(window); }

GLFWwindow* Window::getWindow() { return window; }

Camera& Window::getCamera() { return camera; }

glm::mat4 Window::getViewMatrix() const { return camera.getViewMatrix(); };

glm::mat4 Window::getProjectionMatrix() const
{
    float aspect {static_cast<float>(width) / static_cast<float>(height)};
    return glm::perspective(glm::radians(camera.getZoom()), aspect, 0.1F, 100.0F);
};

bool Window::wasKeyPressed(int key) const
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}

bool Window::shouldClose() const
{
    return static_cast<bool>(glfwWindowShouldClose(window));
}

void Window::createWindow()
{
    window = glfwCreateWindow(width, height, "OpenGL Renderer", nullptr, nullptr);
    if (window == nullptr)
    {
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
}

void Window::swapBuffers() const { glfwSwapBuffers(window); }

void Window::processCameraMovement(float delta_time)
{
    if (!fps_mode)
    {
        return;
    }

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
}

static void initialiseGlfw()
{
    if (!static_cast<bool>(glfwInit()))
    {
        throw std::runtime_error("Failed to start GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, static_cast<int>(true)); // slow!
}

static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
    {
        if (self->fps_mode)
        {
            Gui::enableMouse();
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            glfwSetCursorPos(window, 0.0, 0.0); // ensure no invisible cursor
            self->fps_mode = false;
        }
        else
        {
            Gui::disableMouse();
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            self->getCamera().resetMouse();
            self->fps_mode = true;
        }
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, static_cast<int>(true));
    }
}

static void mouseCallback(GLFWwindow* window, double x_pos, double y_pos)
{
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (!self->fps_mode)
    {
        return;
    }

    self->getCamera().handleMouseCallback(static_cast<float>(x_pos),
                                          static_cast<float>(y_pos));
}

static void scrollCallback(GLFWwindow* window, double x_offset, double y_offset)
{
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    self->getCamera().handleScrollCallback(static_cast<float>(x_offset),
                                           static_cast<float>(y_offset));
}
