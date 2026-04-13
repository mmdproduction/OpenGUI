#include<iostream>
#include"GL/glew.h"

#include"GLFW/glfw3.h"
#include"glm/glm.hpp"

#include"Window.hpp"
#include"EventSystem.hpp"
#include"Renderer.hpp"

int main(void)
{
    if (!Window::windowInit()) return -1;
    

    Window window = Window(900, 800, "Test");
    EventSystem eventSystem;

    window.makeContextCurrent();

    if(glewInit()) return -1;
    Renderer render = Renderer(900, 800, "shaders/vert.glsl", "shaders/frag.glsl");

    eventSystem.setKeyCallback(window.getWindow());
    eventSystem.setMouseButtonCallback(window.getWindow());
    while (!window.isWindowShouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        render.begin();

        if(eventSystem.isButtonUp(GLFW_MOUSE_BUTTON_LEFT)){
             window.setWindowShouldClose(true);
        }

        render.draw({300, 100}, {200, 200}, {1.0f, 0.5f, 0.6f, 0.9f});

        render.end();

        window.swapBuffers();
        eventSystem.update();
    }

    glfwTerminate();
    return 0;
}
