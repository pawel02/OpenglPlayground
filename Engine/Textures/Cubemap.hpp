#pragma once
#include <vector>
#include <string>

#include "../Renderer/Camera.hpp"

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
		Cubemap(Camera* camera) noexcept
			:_VAO{ std::move(Engine::Meshes::createSimpleCube()) },
			_camera{camera},
			_program{"E:\\pawel\\coding(learning)\\c++\\PlayingWithOpenGL\\Engine\\Assets\\Shaders\\cubemap_vs.glsl",
		             "E:\\pawel\\coding(learning)\\c++\\PlayingWithOpenGL\\Engine\\Assets\\Shaders\\cubemap_fs.glsl" }
		{
			loadCubemap();
		}

		Cubemap(std::vector<const char*> faces, Camera* camera) noexcept
			:_faces{ faces }, _VAO{std::move(Engine::Meshes::createSimpleCube())},
			_camera{camera},
			_program{ "E:\\pawel\\coding(learning)\\c++\\PlayingWithOpenGL\\Engine\\Assets\\Shaders\\cubemap_vs.glsl",
					  "E:\\pawel\\coding(learning)\\c++\\PlayingWithOpenGL\\Engine\\Assets\\Shaders\\cubemap_fs.glsl" }
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
		Camera* _camera;

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