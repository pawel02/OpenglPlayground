#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "terrain.hpp"

Terrain::Terrain(unsigned int width, unsigned int height, const std::string& shaderPath) noexcept
	:_width{ width }, _height{ height }, _shader{
		shaderPath + "terrain.vert",
		shaderPath + "terrain.frag"
	}
{
	_indexes.reserve(1024 * 10);
	createTerrain();
}

void Terrain::createTerrain() noexcept
{
	// join a bunch of planes together
	_indexes.emplace_back(24);
	_indexes.emplace_back(25);
	_indexes.emplace_back(26);
	_indexes.emplace_back(27);
	_indexes.emplace_back(28);
	_indexes.emplace_back(29);
	_indexes.emplace_back(30);

	_VAO = std::move(Engine::VertexArray<float, unsigned int>{
		Engine::Meshes::Cube, sizeof(Engine::Meshes::Cube), 
		_indexes.data(), static_cast<int>(_indexes.size() * sizeof(unsigned int)),
		{
			Engine::VertexAttribLayout{3, GL_FLOAT, GL_FALSE, 8 * sizeof(float)},
			Engine::VertexAttribLayout{3, GL_FLOAT, GL_FALSE, 8 * sizeof(float)},
			Engine::VertexAttribLayout{2, GL_FLOAT, GL_FALSE, 8 * sizeof(float)}
		}
	});
	
	_VAO.CreateVertexArray();

	glm::mat4 model = glm::translate(glm::mat4{ 1.0f }, glm::vec3(0.0f, -2.0f, 0.0f));
	_shader.setUniformMat4f("model", model);

}

void Terrain::draw() noexcept
{
	_shader.bind();
	_VAO.bind();
	glDrawElements(GL_TRIANGLES, _VAO.getCount(), GL_UNSIGNED_INT, 0);
}