#include"GLFW/glfw3.h"
#include"glm/glm.hpp"

#include"Window.hpp"

int main(void)
{
    if (!Window::windowInit()) return -1;

    Window window = Window(600, 400, "Test");

    window.makeContextCurrent();

    while (!window.isWindowShouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        window.swapBuffers();

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
