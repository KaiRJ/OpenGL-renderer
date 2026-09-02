#ifndef WINDOW_H
#define WINDOW_H
#define GLFW_INCLUDE_NONE

#include "Camera.hpp"

#include <GLFW/glfw3.h>

class Window
{
  public:
    Window();
    ~Window();

    Camera& getCamera();
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

    bool wasKeyPressed(int key) const;
    void processInput(float delta_time);
    bool shouldClose() const;
    void swapBuffers() const;

  private:
    void createWindow();

    GLFWwindow* window {};
    Camera camera {};

    const float width {800.0};
    const float height {600.0};
};

#endif
