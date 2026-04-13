cmake_minimum_required(VERSION 3.16)
project(OpenGUI CXX)
set(CMAKE_CXX_STANDARD 20)


set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/)
set(GRAPHICS ${SRC}Graphics/)

find_package(OpenGL REQUIRED)


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)


add_subdirectory(libs/glfw)
add_subdirectory(libs/glm)
add_subdirectory(libs/glew-2.3.1/build/cmake)

add_executable(test main.cpp ${SRC}Window/Window.cpp ${SRC}EventSystem/EventSystem.cpp ${GRAPHICS}ShaderLoader/ShaderLoader.cpp ${GRAPHICS}Renderer/Renderer.cpp)
target_link_libraries(test
    PUBLIC
    glfw
    glm::glm
    OpenGL::GL
    glew_s
)

target_include_directories(test PUBLIC
     ${SRC}Window/
     ${SRC}EventSystem/
     ${CMAKE_CURRENT_SOURCE_DIR}/libs/glew-2.3.1/include
     ${GRAPHICS}Renderer/
     )
