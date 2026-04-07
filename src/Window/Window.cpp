#include"Window.hpp"

Window::Window(uint16_t w, uint16_t h, const std::string& t): width(w), height(h), title(t){
        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if(!window){
			glfwTerminate();
			throw std::runtime_error("Ошибка создания окна");
		}
    }

int Window::windowInit(){
	if (!glfwInit()) return 0;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    return 1;
}


void Window::makeContextCurrent(){
    glfwMakeContextCurrent(window);
}
bool Window::isWindowShouldClose(){
    return glfwWindowShouldClose(window);
}
void Window::swapBuffers(){
    glfwSwapBuffers(window);
}

Window::~Window(){
	glfwDestroyWindow(window);
}
    