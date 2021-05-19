/*
This example includes a lot of things
- Loading a basic cube with textures
- Creating a cubemap
- Cube reflecting cubemap
- Cube refracting cubemap
- Creating a perspective camera
- Creating shaders
- Loading models
- Adding a blur effect using framebuffers
*/

#include <iostream>
#include <string>
#include <Engine.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{
	std::string sharedAssetsPath{ "E:/pawel/coding(learning)/c++/PlayingWithOpenGL/shared_assets/" };
	std::string basePath{"E:/pawel/coding(learning)/c++/PlayingWithOpenGL/Example1/shaders/"};

	Engine::Window window{800, 600, "Example window"};

	if (window.createWindow() < 0)
	{
		return -1;
	}
	window.hideCursor();

	//Create the camera
	Engine::CameraPer camera{ 800, 600 };

	//Create simple cube mesh
	Engine::VertexArray<float, unsigned int> VAO{std::move(Engine::Meshes::createCube())};
	VAO.CreateVertexArray();
	Engine::Shader program{ basePath + "basic.vs", basePath + "basic.fs" };

	// Cube reflect
	Engine::VertexArray<float, unsigned int> cube_reflect{ std::move(Engine::Meshes::createCube()) };
	cube_reflect.CreateVertexArray();
	Engine::Shader cube_reflect_program{ basePath + "reflect.vs", basePath + "reflect.fs" };
	glm::mat4 cube_reflect_model{ glm::translate(glm::mat4{1.0f}, glm::vec3{-5.0f, 0.0f, 0.0f}) };
	cube_reflect_program.setUniformMat4f("model", cube_reflect_model);

	// Cube refract
	Engine::VertexArray<float, unsigned int> cube_refract{ std::move(Engine::Meshes::createCube()) };
	cube_refract.CreateVertexArray();
	Engine::Shader cube_refract_program{ basePath + "refract.vs", basePath + "refract.fs" };
	glm::mat4 cube_refract_model{ glm::translate(glm::mat4{1.0f}, glm::vec3{-10.0f, 0.0f, 0.0f}) };
	cube_refract_program.setUniformMat4f("model", cube_refract_model);


	Engine::Texture2D texture{};
	texture.addTexture(sharedAssetsPath + "tex1.jpg");

	//create a default cubemap
	Engine::Cubemap cubemap{&camera};
	
	//create a framebuffer
	Engine::Framebuffer fbo{ 800, 600, { basePath + "fbo.vs", basePath + "fbo.fs" } };
	Engine::Framebuffer::FramebufferStatus fbo_status = fbo.init();
	
	if (fbo_status != Engine::Framebuffer::FramebufferStatus::success)
	{
		std::cout << "Could not create the framebuffer\n";
		return -1;
	}

	//add backpack model
	Engine::Model model_mesh{ sharedAssetsPath + "backpack/backpack.obj" };
	Engine::Shader model_program{basePath + "model.vs", basePath + "model.fs"};

	//translate the model a little to the right
	glm::mat4 model{ 1.0f };
	model = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f));
	model_program.setUniformMat4f("model", model);

	float deltaTime = 0.0f;
	float previousTime = 0.0f;
	while (window.isOpen())
	{
		//draw to my custom buffer
		fbo.bind();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		
		deltaTime = (float)glfwGetTime() - previousTime;
		previousTime = (float)glfwGetTime();
		camera.onUpdate(deltaTime);

		//example of drawing a primitive
		VAO.bind();
		program.bind();
		texture.bindAll();
		glCheckError(glDrawArrays(GL_TRIANGLES, 0, 36));


		//draw the two cubes
		cubemap.bind();

		cube_reflect.bind();
		cube_reflect_program.bind();
		glCheckError(glDrawArrays(GL_TRIANGLES, 0, 36));

		cube_refract.bind();
		cube_refract_program.bind();
		glCheckError(glDrawArrays(GL_TRIANGLES, 0, 36));


		//draw the model
		model_mesh.Draw(model_program);

		//draw the cubemap
		cubemap.draw();

		//draw to the default framebuffer
		fbo.draw();

		glfwSwapBuffers(window.getWindowPointer());
		glfwPollEvents();
	}

	return 0;
}