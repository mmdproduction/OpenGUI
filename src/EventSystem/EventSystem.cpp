#include"EventSystem.hpp"


EventSystem* EventSystem::instance = nullptr;


EventSystem::EventSystem(){
    for(uint16_t i = 0; i < NUM_OF_ALL_CODES; ++i){
        _keys[i] = false;
        _last_keys[i] = false;
    }
    instance = this;
}

EventSystem::~EventSystem() {
    if (instance == this) {
        instance = nullptr;
    }
}

void EventSystem::keyCallback(GLFWwindow* window, int keycode, int scancode, int action, int mods){
    if(instance && keycode < MAX_NUM_OF_KEYBOARD_KEYDODES && keycode >= 0){
        switch (action)
        {
        case GLFW_PRESS:
           instance->_keys[keycode] = true;
            break;
        case GLFW_RELEASE:
            instance->_keys[keycode] = false;
        }
    }

}
void EventSystem::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
    if(instance && button < MAX_NUM_OF_MOUSE_BUTTONS && button >= 0){
        switch (action)
        {
        case GLFW_PRESS:
           instance->_keys[button + MAX_NUM_OF_KEYBOARD_KEYDODES] = true;
            break;
        case GLFW_RELEASE:
            instance->_keys[button + MAX_NUM_OF_KEYBOARD_KEYDODES] = false;
        }
    } 
}

void EventSystem::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos){
    int height;
    glfwGetWindowSize(window, nullptr, &height);
    instance->mouseX = xpos;
    instance->mouseY = height - ypos;
    std::cout << instance->getMouseX() << " " << instance->getMouseY() << std::endl;
}

void EventSystem::setCursorPosCallback(GLFWwindow* window){
    glfwSetCursorPosCallback(window, cursorPositionCallback);
}

void EventSystem::setMouseButtonCallback(GLFWwindow* window){
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
}

void EventSystem::setKeyCallback(GLFWwindow* window){
    glfwSetKeyCallback(window, keyCallback);
}

void EventSystem::update(){
    for(uint16_t i = 0; i < NUM_OF_ALL_CODES; ++i){
        _last_keys[i] = _keys[i];
    }
    glfwPollEvents();
}

bool EventSystem::isKeyPressed(int keycode){
    if((keycode < 0 || keycode >= MAX_NUM_OF_KEYBOARD_KEYDODES)) return false;
    return _keys[keycode] && !_last_keys[keycode];
}

bool EventSystem::isKeyUp(int keycode){
    if((keycode < 0 || keycode >= MAX_NUM_OF_KEYBOARD_KEYDODES)) return false;
    return !_keys[keycode] && _last_keys[keycode];
}

bool EventSystem::isKeyDown(int keycode){
    if((keycode < 0 || keycode >= MAX_NUM_OF_KEYBOARD_KEYDODES)) return false;
    return _keys[keycode];
}

bool EventSystem::isButtonClicked(int button){
    if((button < 0 || button >= MAX_NUM_OF_MOUSE_BUTTONS)) return false;
    return _keys[button + MAX_NUM_OF_KEYBOARD_KEYDODES] && !_last_keys[button + MAX_NUM_OF_KEYBOARD_KEYDODES];
}

bool EventSystem::isButtonUp(int button){
    if((button < 0 || button >= MAX_NUM_OF_MOUSE_BUTTONS)) return false;
    return !_keys[button + MAX_NUM_OF_KEYBOARD_KEYDODES] && _last_keys[button + MAX_NUM_OF_KEYBOARD_KEYDODES];
}

bool EventSystem::isButtonDown(int button){
    if((button < 0 || button >= MAX_NUM_OF_MOUSE_BUTTONS)) return false;
    return _keys[button + MAX_NUM_OF_KEYBOARD_KEYDODES];
}

EventSystem* EventSystem::getInstance(){
    return instance;
}