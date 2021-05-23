#pragma once
#include <vector>
#include "../Textures/Texture2D.hpp"
#include "../Shaders/Shader.hpp"
#include "../Core/VertexArray.hpp"

namespace Engine
{
class Mesh
{
public:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	Texture2D* textures;

	Mesh(std::vector<float> vertices, std::vector<unsigned int> indices, 
		Texture2D* textures) noexcept;

	Mesh(Mesh&& other) noexcept;

	void Draw(Shader& shader);
	const VertexArray<float, unsigned int>& getVAO() const noexcept { return VAO; }
private:
	VertexArray<float, unsigned int> VAO;
};

}