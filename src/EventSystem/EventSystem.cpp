#include"EventSystem.hpp"

void EventSystem::keyCallback(GLFWwindow* window, int keycode, int scancode, int action, int mods){
    if(keycode < MAX_KEYBOARD_KEYCODE){
        switch (action)
        {
        case GLFW_PRESS:
            _keys[keycode] = true;
            break;
        case GLFW_RELEASE:
            _keys[keycode] = false;
        }
    }

}

void EventSystem::update(){
    
    for(uint16_t i = 0; i < MAX_KEYBOARD_KEYCODE + 1; ++i){
        _last_keys[i] = _keys[i];
    }
}

bool EventSystem::isKeyPressed(int keycode){

}

bool EventSystem::isKeyUp(int keycode){

}

bool EventSystem::isKeyDown(int keycode){

}