#include <iostream>
#include <Engine.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{
	Engine::Window window{800, 600, "Example window"};
	window.createWindow();

	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	//lets create a triangle
	unsigned int VAO, VBO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(0);

	Engine::Shader program{ "E:\\pawel\\coding(learning)\\c++\\PlayingWithOpenGL\\Example1\\shaders\\vs.glsl", "E:\\pawel\\coding(learning)\\c++\\PlayingWithOpenGL\\Example1\\shaders\\fs.glsl" };

	//Create a uniform buffer
	Engine::UniformBuffer ubo{16};
	ubo.bindBufferBlock(2);
	glm::vec4 data{ 0.5f, 0.5f, 0.5f, 1.0f };
	ubo.subData(glm::value_ptr(data), 0, sizeof(glm::vec4));

	while (window.isOpen())
	{
		glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window.getWindowPointer());
		glfwPollEvents();
	}

	return 0;
}