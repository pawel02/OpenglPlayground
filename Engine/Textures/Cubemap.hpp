#pragma once
#include <vector>
#include <string>

#include "../Assets/Meshes/Cubes.hpp"
#include "../Core/VertexArray.hpp"
#include "../Shaders/Shader.hpp"


/*
Cubemap wrapper
Creates a cubemap with default shaders
*/
namespace Engine
{
	class Cubemap {

	public:
		//default cubemap
		Cubemap() noexcept
			:_VAO
		{
		 Meshes::simepleCube, sizeof(Engine::Meshes::simepleCube),
			{
			 VertexAttribLayout{3, GL_FLOAT, GL_FALSE, 3 * sizeof(float)}
			}
		}
		{
			loadCubemap();
		}

		Cubemap(std::vector<const char*> faces) noexcept
			:_faces{ faces }, _VAO
			{
			 Meshes::simepleCube, sizeof(Engine::Meshes::simepleCube),
				{
				 VertexAttribLayout{3, GL_FLOAT, GL_FALSE, 3 * sizeof(float)}
				}
			}
		{
			loadCubemap();
		}

		void loadCubemap() noexcept;

		//bind the cubemap texture only
		void bind() noexcept;
		void draw() noexcept;

	private:
		VertexArray<float, unsigned int> _VAO;
		Shader _program;

		std::vector<const char*> _faces =
		{
			"E:\\pawel\\coding(learning)\\c++\\PlayingWithOpenGL\\Engine\\Assets\\Models\\skybox\\right.jpg",
			"E:\\pawel\\coding(learning)\\c++\\PlayingWithOpenGL\\Engine\\Assets\\Models\\skybox\\left.jpg",
			"E:\\pawel\\coding(learning)\\c++\\PlayingWithOpenGL\\Engine\\Assets\\Models\\skybox\\top.jpg",
			"E:\\pawel\\coding(learning)\\c++\\PlayingWithOpenGL\\Engine\\Assets\\Models\\skybox\\bottom.jpg",
			"E:\\pawel\\coding(learning)\\c++\\PlayingWithOpenGL\\Engine\\Assets\\Models\\skybox\\front.jpg",
			"E:\\pawel\\coding(learning)\\c++\\PlayingWithOpenGL\\Engine\\Assets\\Models\\skybox\\back.jpg"
		};

		unsigned int _cubemapTex = 0;
	};
}