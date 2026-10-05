#ifndef MYGUI_H
#define MYGUI_H

#include <GLFW/glfw3.h>

class Gui
{
  public:
    static void initialise(GLFWwindow* window);
    static void shutdown();
    static void newFrame();
    static void render();
    static void enableMouse();
    static void disableMouse();
};

#endif
