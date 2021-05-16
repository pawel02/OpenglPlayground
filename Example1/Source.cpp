#include <iostream>
#include <Engine.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{
	Engine::Window window{800, 600, "Example window"};

	if (window.createWindow() < 0)
	{
		return -1;
	}
	window.hideCursor();

	//Create the camera
	Engine::CameraPer camera{ 800, 600};

	//Create the example triangle
	Engine::VertexArray<float, unsigned int> VAO{Engine::Meshes::createSimpleCube()};

	VAO.CreateVertexArray();

	Engine::Shader program{ "E:\\pawel\\coding(learning)\\c++\\PlayingWithOpenGL\\Example1\\shaders\\vs.glsl", "E:\\pawel\\coding(learning)\\c++\\PlayingWithOpenGL\\Example1\\shaders\\fs.glsl" };

	float deltaTime = 0.0f;
	float previousTime = 0.0f;
	while (window.isOpen())
	{
		glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		
		deltaTime = (float)glfwGetTime() - previousTime;
		previousTime = (float)glfwGetTime();
		camera.onUpdate(deltaTime);

		glDrawArrays(GL_TRIANGLES, 0, 36);



		glfwSwapBuffers(window.getWindowPointer());
		glfwPollEvents();
	}

	return 0;
}