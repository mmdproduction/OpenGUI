#pragma once
#include"Window.hpp"
#include<vector>


#define MAX_NUM_OF_KEYBOARD_KEYDODES 349
#define MAX_NUM_OF_MOUSE_BUTTONS 8
#define NUM_OF_ALL_CODES MAX_NUM_OF_KEYBOARD_KEYDODES + MAX_NUM_OF_MOUSE_BUTTONS

class EventSystem{
    private:
    bool _keys[NUM_OF_ALL_CODES];
    bool _last_keys[NUM_OF_ALL_CODES];
    double mouseX = 0,
    mouseY = 0,
    scrollY = 0;
    std::vector<uint32_t> typed_char;

    static void keyCallback(GLFWwindow* window, int keycode, int scancode, int action, int mods);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
    static void charCallback(GLFWwindow* window, unsigned int codepoint);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static EventSystem* instance;

    public:

    EventSystem();

    void setKeyCallback(GLFWwindow* window);
    void setCharCallback(GLFWwindow* window);
    void setMouseButtonCallback(GLFWwindow* window);
    void setCursorPosCallback(GLFWwindow* window);
    void setScrollCallback(GLFWwindow* window);

    void update();
    void clearTypedChar(){ typed_char.clear(); }
    void resetScrollY(){ scrollY = 0.0f; }


    bool isKeyPressed(int keycode);
    bool isKeyUp(int keycode);
    bool isKeyDown(int keycode);
    bool isButtonClicked(int button);
    bool isButtonDown(int button);
    bool isButtonUp(int button);


    double getMouseX(){return mouseX; }
    double getMouseY(){return mouseY; }
    double getScrollY(){return scrollY; }
    const std::vector<uint32_t>& getTypedChar(){ return typed_char; }

    static EventSystem* getInstance();

    ~EventSystem();
};