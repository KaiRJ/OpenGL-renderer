#ifndef DEBUG_H
#define DEBUG_H

#include <glad/glad.h>

namespace Debug
{

    void initialiseDebugOutput();

    void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int message_id,
                                GLenum severity, GLsizei length, const char* message,
                                const void* user_param);
} // namespace Debug

#endif
