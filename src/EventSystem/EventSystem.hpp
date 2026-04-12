#pragma once
#include"Window.hpp"


#define MAX_NUM_OF_KEYBOARD_KEYDODES 349
#define MAX_NUM_OF_MOUSE_BUTTONS 8
#define NUM_OF_ALL_CODES MAX_NUM_OF_KEYBOARD_KEYDODES + MAX_NUM_OF_MOUSE_BUTTONS

/// @brief переделать!!!
class EventSystem{
    private:
    bool _keys[NUM_OF_ALL_CODES];
    bool _last_keys[NUM_OF_ALL_CODES];

    static void keyCallback(GLFWwindow* window, int keycode, int scancode, int action, int mods);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static EventSystem* instance;

    public:
    EventSystem();

    void setKeyCallback(GLFWwindow* window);
    void setMouseButtonCallback(GLFWwindow* window);
    void update();

    bool isKeyPressed(int keycode);
    bool isKeyUp(int keycode);
    bool isKeyDown(int keycode);
    bool isButtonClicked(int button);
    bool isButtonDown(int button);
    bool isButtonUp(int button);

    static EventSystem* getInstance();

    ~EventSystem();
};