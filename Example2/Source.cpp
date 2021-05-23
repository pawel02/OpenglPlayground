#include <iostream>
#include <string>
#include <Engine.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{
	std::string sharedAssetsPath{ "E:/pawel/coding(learning)/c++/PlayingWithOpenGL/shared_assets/" };
	std::string basePath{"E:/pawel/coding(learning)/c++/PlayingWithOpenGL/Example2/shaders/"};

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
	Engine::Shader program{ basePath + "basic.vs", basePath + "lights.fs" };

	//pointlight
	Engine::VertexArray<float, unsigned int> pointLight{ std::move(Engine::Meshes::createCube()) };
	pointLight.CreateVertexArray();
	Engine::Shader pointLightProgram{ basePath + "basic.vs", basePath + "basic.fs" };
	
	glm::vec3 pointLightPos{ 2.0f, 0.5f, 0.0f };
	glm::mat4 pointLightModel{ 1.0f };
	pointLightModel = glm::translate(pointLightModel, pointLightPos);
	pointLightModel = glm::scale(pointLightModel, glm::vec3(0.1f));
	pointLightProgram.setUniformMat4f("model", pointLightModel);
	pointLightProgram.setUniform4f("color", 1.0f, 0.5f, 0.5f, 1.0f);

	//spotlight
	Engine::VertexArray<float, unsigned int> SpotLight{ std::move(Engine::Meshes::createCube()) };
	SpotLight.CreateVertexArray();
	Engine::Shader SpotLightProgram{ basePath + "basic.vs", basePath + "basic.fs" };
	
	glm::vec3 spotLightPos{ -1.0f, -3.0f, 1.0f };
	glm::mat4 spotLightModel{ 1.0f };
	spotLightModel = glm::translate(spotLightModel, spotLightPos);
	spotLightModel = glm::scale(spotLightModel, glm::vec3(0.1f));
	SpotLightProgram.setUniformMat4f("model", spotLightModel);
	SpotLightProgram.setUniform4f("color", 0.0f, 0.5f, 0.5f, 1.0f);

	//set the overall light direction
	program.setUniform3f("dirLight.direction", -0.2f, -1.0f, -0.3f);
	program.setUniform3f("dirLight.ambient", 0.5f, 0.5f, 0.5f);
	program.setUniform3f("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	program.setUniform3f("dirLight.specular", 0.5f, 0.5f, 0.5f);

	//create a pointlight
	program.setUniform3f("pointLights[0].position", pointLightPos);
	program.setUniform3f("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
	program.setUniform3f("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
	program.setUniform3f("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
	program.setUniform1f("pointLights[0].constant", 1.0f);
	program.setUniform1f("pointLights[0].linear", 0.09);
	program.setUniform1f("pointLights[0].quadratic", 0.032);

	// spotLight
	program.setUniform3f("spotLight.position", spotLightPos);
	program.setUniform3f("spotLight.direction", glm::vec3(0.0f, 1.0f, 0.0f));
	program.setUniform3f("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	program.setUniform3f("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	program.setUniform3f("spotLight.specular", 1.0f, 1.0f, 1.0f);
	program.setUniform1f("spotLight.constant", 1.0f);
	program.setUniform1f("spotLight.linear", 0.09);
	program.setUniform1f("spotLight.quadratic", 0.032);
	program.setUniform1f("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	program.setUniform1f("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

	//set the material texture
	program.setUniform3f("material.diffuse", 0.5f, 1.0f, 0.02f);
	program.setUniform3f("material.specular", 1.0f, 1.0f, 1.0f);
	program.setUniform1f("material.shininess", 256.0f);

	glm::mat4 model{ 1.0f };
	model = glm::translate(model, glm::vec3(-1.0f, 1.0f, 1.0f));
	program.setUniformMat4f("model", model);

	float deltaTime = 0.0f;
	float previousTime = 0.0f;
	while (window.isOpen())
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		
		deltaTime = (float)glfwGetTime() - previousTime;
		previousTime = (float)glfwGetTime();
		camera.onUpdate(deltaTime);

		VAO.bind();
		program.bind();
		glCheckError(glDrawArrays(GL_TRIANGLES, 0, 36));

		//draw the positions of the lights
		pointLight.bind();
		pointLightProgram.bind();
		glCheckError(glDrawArrays(GL_TRIANGLES, 0, 36));

		SpotLight.bind();
		SpotLightProgram.bind();
		glCheckError(glDrawArrays(GL_TRIANGLES, 0, 36));

		glfwSwapBuffers(window.getWindowPointer());
		glfwPollEvents();
	}

	return 0;
}