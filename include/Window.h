#ifndef WINDOW_H
#define WINDOW_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Window
{
  public:
    Window();

    bool ShouldClose();
    void ProcessInput();
    void SwapBuffers();

  private:
    GLFWwindow* window {nullptr};

    void CreateWindow();
};

#endif
