#pragma once
#include"Window.hpp"


#define MAX_KEYBOARD_KEYCODE 348


class EventSystem{
    private:
    bool static _keys[MAX_KEYBOARD_KEYCODE] = {false};
    bool static _last_keys[MAX_KEYBOARD_KEYCODE] = {false};
    void static keyCallback(GLFWwindow* window, int keycode, int scancode, int action, int mods);
    public:

    void static update();
    bool static isKeyPressed(int keycode);
    bool static isKeyUp(int keycode);
    bool static isKeyDown(int keycode);

};