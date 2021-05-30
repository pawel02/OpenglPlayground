#pragma once
#include <vector>
#include <Engine.hpp>

class Terrain
{
public:
	Terrain(unsigned int width, unsigned int height, const std::string& shaderPath) noexcept;
	~Terrain() = default;

	void createTerrain() noexcept;
	void draw() noexcept;

private:
	std::vector<unsigned int> _indexes;

	Engine::Shader _shader;
	Engine::VertexArray<float, unsigned int> _VAO;

	unsigned int _width = 0;
	unsigned int _height = 0;

	// All of the planes that will be used to create the terrain
	const float _planeFront[48] = {
		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
		-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f
	};

	const float _planeBack[48] = {
		-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	};

	const float _planeLeft[48] = {
		-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,	0.0f,  0.0f, 0.0f,
		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,	0.0f,  0.0f, 1.0f,
		-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,	0.0f,  1.0f, 1.0f,
		-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,	0.0f,  1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,	0.0f,  1.0f, 0.0f,
		-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,	0.0f,  0.0f, 0.0f,
	};

	const float _planeRight[48] = {
		 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	};

	const float _planeTop[48] = {
		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	};

	const float _planeBottom[48] = {
		 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	};

};