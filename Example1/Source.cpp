#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <Engine.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

int main()
{

	std::cout << func() << "\n";
	Assimp::Importer importer;

	int windowWidth = 800;
	int windowHeight = 600;


	if (!glfwInit())
	{
		std::cout << "Could not initialize GLFW";
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Example window", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create a window GLFW\n";
		return -1;
	}
	
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Could not initialize GLAD context\n";
		return -1;
	}

	glViewport(0, 0, windowWidth, windowHeight);

	//enable all the defaults that should be set
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_STENCIL_TEST);

	glEnable(GL_CULL_FACE);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 
	//mainloop
	while (!glfwWindowShouldClose(window))
	{

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}