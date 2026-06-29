set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

cmake_minimum_required(VERSION 3.16...3.27)
project(LearnOpenGL)

# Find GLFW using pkg-config
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

# Source files
file(GLOB SOURCES src/* externals/glad/glad.c)

# Create executable
add_executable(main main.cpp ${SOURCES})

# Include GLFW headers
target_include_directories(main
  PRIVATE
  ${GLFW_INCLUDE_DIRS}
  include
  externals/
)

# Link GLFW and OpenGL (and dl, pthread, X11 for Linux)
target_link_libraries(main
    ${GLFW_LIBRARIES}
    GL
    dl
    pthread
    X11
    Xrandr
    Xi
)

# Copy shaders into build directory
file(GLOB SHADER_FILES "${CMAKE_SOURCE_DIR}/shaders/*")
foreach(shader ${SHADER_FILES})
    get_filename_component(shader_name ${shader} NAME)

    add_custom_command(TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${shader}
            ${CMAKE_BINARY_DIR}/shaders/${shader_name}
    )
endforeach()
