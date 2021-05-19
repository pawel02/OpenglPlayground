#include "Mesh.hpp"
#include <string>

namespace Engine
{

	Mesh::Mesh(std::vector<float> vertices, std::vector<unsigned int> indices, 
		Texture2D* _textures) noexcept
		:VAO{
		vertices.data(), vertices.size() * sizeof(float),
		indices.data(), indices.size() * sizeof(unsigned int),
	{
		VertexAttribLayout{3, GL_FLOAT, GL_FALSE, 8 * sizeof(float)},
		VertexAttribLayout{3, GL_FLOAT, GL_FALSE, 8 * sizeof(float)},
		VertexAttribLayout{2, GL_FLOAT, GL_FALSE, 8 * sizeof(float)}
	}
	},
		textures{ _textures },
		vertices{ vertices },
		indices{ indices }
	{
		VAO.CreateVertexArray();
	}

	Mesh::Mesh(Mesh&& other) noexcept
		:VAO{ std::move(other.VAO) },
		vertices{ std::move(other.vertices) },
		indices{ std::move(other.indices) },
		textures{ other.textures }
	{
		other.textures = nullptr;
	}

	void Mesh::Draw(Shader& shader)
	{
		shader.bind();
		//bind all the textures
		textures->bindAll();
		//const auto& all_textures = textures.get_textures();
		//shader.setUniform1i("material.diffuse", 0);
		/*for (size_t i = 0; i < all_textures.size(); i++)
		{
			shader.set_uniform_1i(std::string{ "material[" + std::to_string(i) + "].diffuse" }.c_str(), i);
		}*/

		//draw the mesh
		VAO.bind();
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}

}