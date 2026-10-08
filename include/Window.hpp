#ifndef WINDOW_H
#define WINDOW_H

#include "Camera.hpp"
#include <GLFW/glfw3.h>

class Window
{
  public:
    Window();
    ~Window();

    // delete the copy constructor and assignment
    Window(const Window& window) = delete;
    Window& operator=(const Window& window) = delete;

    [[nodiscard]] GLFWwindow* getWindow();
    [[nodiscard]] Camera& getCamera();
    [[nodiscard]] glm::mat4 getViewMatrix() const;
    [[nodiscard]] glm::mat4 getProjectionMatrix() const;

    [[nodiscard]] bool wasKeyPressed(int key) const;
    [[nodiscard]] bool shouldClose() const;
    void swapBuffers() const;
    void processCameraMovement(float delta_time);

    bool fps_mode {false}; // TODO: move this to private

  private:
    void createWindow();

    GLFWwindow* window {};
    Camera camera;

    static constexpr int width {800};
    static constexpr int height {600};
};

static void initialiseGlfw();
static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void mouseCallback(GLFWwindow* window, double x_pos, double y_pos);
static void scrollCallback(GLFWwindow* window, double x_offset, double y_offset);

#endif
