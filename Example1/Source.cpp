#include <Engine.h>

int main()
{
	GLFWwindow* window = Engine::createWindow();

	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}