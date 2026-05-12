set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

cmake_minimum_required(VERSION 3.16...3.27)
project(LearnOpenGL)

# Add include directory for glad
include_directories(include)

# Find GLFW using pkg-config
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

# Source files
set(SOURCES
    main.cpp
    glad.c
)

# Create executable
add_executable(main ${SOURCES})

# Include GLFW headers
target_include_directories(main PRIVATE ${GLFW_INCLUDE_DIRS})

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
