#include <Engine.hpp>

#include <assimp/Importer.hpp>

int main()
{
	Engine::Window window{800, 600, "Example window"};
	window.createWindow();

	while (window.isOpen())
	{
		glfwSwapBuffers(window.getWindowPointer());
		glfwPollEvents();
	}

	return 0;
}