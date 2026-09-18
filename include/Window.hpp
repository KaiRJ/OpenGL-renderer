#ifndef WINDOW_H
#define WINDOW_H

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
    Camera camera;

    const int width {800};
    const int height {600};
};

#endif
