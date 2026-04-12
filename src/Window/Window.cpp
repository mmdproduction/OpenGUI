#include"Window.hpp"

Window::Window(uint16_t w, uint16_t h, const std::string& t): width(w), height(h), title(t){
        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if(!window){
			glfwTerminate();
			throw std::runtime_error("ERROR::WINDOW::WINDOW_NOT_SUCCESFULLY_CREATE");
		}
    }

int Window::windowInit(){
	if (!glfwInit()) return 0;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    return 1;
}

void Window::framebuffer_size_callback(GLFWwindow* window, int w, int h){
	glViewport(0, 0, w, h);
}

void Window::setFramebufferSizeCallback(){
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}


void Window::makeContextCurrent(){
    glfwMakeContextCurrent(window);
}
bool Window::isWindowShouldClose(){
    return glfwWindowShouldClose(window);
}
void Window::setWindowShouldClose(bool flag){
	glfwSetWindowShouldClose(window, flag);
}
void Window::swapBuffers(){
	glfwSwapBuffers(window);
}



GLFWwindow* Window::getWindow(){
	return window;
}
Window::~Window(){
	glfwDestroyWindow(window);
}


    