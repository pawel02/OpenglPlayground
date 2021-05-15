#include "Window.hpp"

#include <iostream>

namespace Engine
{

Window::Window(int width, int height, const char* name) noexcept
    :_windowData{width, height, name, nullptr}
{}
Window::Window(int width, int height, const char* name, GLFWmonitor* monitor) noexcept
    :_windowData{width, height, name, monitor}
{}

Window::~Window() noexcept
{}

int Window::createWindow() noexcept
{
	if (!glfwInit())
	{
		std::cout << "Could not initialize GLFW";
        return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	_window = glfwCreateWindow(_windowData.width, _windowData.height, "Example window", NULL, NULL);

	if (_window == NULL)
	{
		std::cout << "Failed to create a window GLFW\n";
        return -2;
	}
	
	glfwMakeContextCurrent(_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Could not initialize GLAD context\n";
        return -3;
	}

	glViewport(0, 0, _windowData.width, _windowData.height);

	//enable all the testing and blend modes that should be enabled by default
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_STENCIL_TEST);

	glEnable(GL_CULL_FACE);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return 0;
}

bool Window::close() noexcept
{
    glfwSetWindowShouldClose(_window, true);
    return true;
}


}
