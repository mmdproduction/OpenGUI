#pragma once
#include"GLFW/glfw3.h"
#include <string>
#include <stdexcept>
#include<iostream>



class Window{
    private:

    GLFWwindow* window = nullptr;
    std::string title = "";
    uint16_t width = 0;
    uint16_t height = 0;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    public:

    Window(uint16_t w, uint16_t h, const std::string& t);
    ~Window();

    bool isResize;
    static int windowInit();
    void makeContextCurrent(); 
    bool isWindowShouldClose();
    void setWindowShouldClose(bool flag);
    void swapBuffers();
    void setFramebufferSizeCallback();
    uint16_t getWidth();
    uint16_t getHeight();


    GLFWwindow* getWindow();
};