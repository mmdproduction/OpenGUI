#include<iostream>
#include"GLFW/glfw3.h"
#include"glm/glm.hpp"

#include"Window.hpp"
#include"EventSystem.hpp"

int main(void)
{
    if (!Window::windowInit()) return -1;

    Window window = Window(600, 400, "Test");
    EventSystem eventSystem;

    window.makeContextCurrent();
    eventSystem.setKeyCallback(window.getWindow());
    eventSystem.setMouseButtonCallback(window.getWindow());
    while (!window.isWindowShouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        
        if(eventSystem.isButtonUp(GLFW_MOUSE_BUTTON_LEFT)){
             window.setWindowShouldClose(true);
        }
        

        window.swapBuffers();
        eventSystem.update();
    }

    glfwTerminate();
    return 0;
}
