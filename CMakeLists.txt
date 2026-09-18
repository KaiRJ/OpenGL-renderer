cmake_minimum_required(VERSION 3.11)
project(LearnOpenGL LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

# Libraries: GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(Libraries/glfw)

# Libraries: GLAD (compiled as part of main target, need to get yourself)
add_library(glad STATIC Libraries/glad/src/glad.c)
target_include_directories(glad PUBLIC Libraries/glad/include/)

# Create executable
file(GLOB SOURCES main.cpp src/*)
add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE
  GLFW_INCLUDE_NONE
  PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")

target_include_directories(${PROJECT_NAME} PRIVATE
  include
  Libraries/glm/
  Libraries/stb/)

add_compile_options(-ggdb
  -pedantic-errors
  -Wall
  -Weffc++
  -Wextra
  -Wconversion
  -Wsign-conversion
  -Werror)

target_link_libraries(${PROJECT_NAME} PRIVATE
  glfw
  glad
)

# Create shader directory in build folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory
  ${CMAKE_BINARY_DIR}/shaders
)

# Copy shaders into build/shader directory
file(GLOB SHADERS "${CMAKE_SOURCE_DIR}/shaders/*")
foreach(shader ${SHADERS})
  get_filename_component(shader_name ${shader} NAME)

  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${shader}
    ${CMAKE_BINARY_DIR}/shaders/${shader_name}
  )
endforeach()
