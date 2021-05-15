#include "Engine.h"

#include <glm/glm.hpp>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Engine
{
	GLFWwindow* window = nullptr;

GLFWwindow* createWindow()
{
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

	window = glfwCreateWindow(windowWidth, windowHeight, "Example window", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create a window GLFW\n";
	}
	
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Could not initialize GLAD context\n";
	}

	glViewport(0, 0, windowWidth, windowHeight);

	//enable all the defaults that should be set
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_STENCIL_TEST);

	glEnable(GL_CULL_FACE);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return window;
 
}
}
