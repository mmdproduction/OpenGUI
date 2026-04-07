#pragma once
#include"GLFW/glfw3.h"
#include <string>
#include <stdexcept>


class Window{
    private:

    GLFWwindow* window = nullptr;
    std::string title = "";
    uint16_t width = 0;
    uint16_t height = 0;

    public:

    Window(uint16_t w, uint16_t h, const std::string& t);
    ~Window();

    static int windowInit();
    void makeContextCurrent(); 
    bool isWindowShouldClose();
    void swapBuffers();

};