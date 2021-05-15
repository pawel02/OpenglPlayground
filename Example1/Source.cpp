#include <Engine.h>

#include <assimp/Importer.hpp>

int main()
{
	GLFWwindow* window = Engine::createWindow();
	Assimp::Importer importer;

	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}