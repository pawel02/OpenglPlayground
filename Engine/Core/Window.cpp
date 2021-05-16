#include "Window.hpp"
#include "../Events/KeyboardEvents.hpp"
#include "../Events/MouseEvents.hpp"
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

	registerEvents();

    return 0;
}

bool Window::close() noexcept
{
    glfwSetWindowShouldClose(_window, true);
    return true;
}

void Window::registerEvents() noexcept
{
	//store the data pointer in glfw
	glfwSetWindowUserPointer(_window, &_windowData);

	glfwSetFramebufferSizeCallback(_window, [](GLFWwindow* window, int width, int height) {
		WindowData& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));
		data.width = width;
		data.height = height;

		Events::WindowResizeEvent ev{width, height};
		Events::EventBus::publish<Events::WindowResizeEvent>(&ev);
	});


	glfwSetWindowCloseCallback(_window, [](GLFWwindow* window) {
		Events::WindowCloseEvent ev{};
		Events::EventBus::publish<Events::WindowCloseEvent>(&ev);
	});

	//all of the keycallbacks
	glfwSetKeyCallback(_window, []
	(GLFWwindow* window, int key, int scancode, int action, int mods) {
		switch (action)
		{
			case GLFW_PRESS:
			{
				Events::KeyPressedEvent ev{ key };
				Events::EventBus::publish<Events::KeyPressedEvent>(&ev);
				break;
			}
			case GLFW_RELEASE:
			{
				Events::KeyReleasedEvent ev{ key };
				Events::EventBus::publish<Events::KeyReleasedEvent>(&ev);
				break;
			}
		}
	});

	glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double xpos, double ypos) {
		Events::MouseMovedEvent ev{xpos, ypos};
		Events::EventBus::publish<Events::MouseMovedEvent>(&ev);
	});

	//exit when pressing esc by default
	Events::EventBus::subscribe<Events::KeyPressedEvent>([&](Events::BasicEvent* ev)
		{
			Events::KeyPressedEvent* _ev = static_cast<Events::KeyPressedEvent*>(ev);
			switch (_ev->getCode())
			{
				case GLFW_KEY_ESCAPE:
				{
					close();
					break;
				}
			}
			return false;
		});
}

bool Window::resize(Events::WindowResizeEvent* ev)
{
	glm::vec2 size = ev->getSize();

	_windowData.width = size.x;
	_windowData.height = size.y;

	glViewport(0, 0, size.x, size.y);
	return true;
}

}
