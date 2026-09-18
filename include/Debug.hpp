#ifndef DEBUG_H
#define DEBUG_H

#include <GLFW/glfw3.h>
#include <glad/glad.h>

void initialiseDebugOutput();

void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity,
                            GLsizei length, const char* message, const void* userParam);

#endif
