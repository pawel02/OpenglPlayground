#pragma once
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../Shaders/Shader.hpp"
#include "../Textures/Texture2D.hpp"
#include "Mesh.hpp"

namespace Engine
{

class Model
{
public:
	Model(const std::string& filepath) noexcept;

	void Draw(Shader& shader);
	const std::vector<Mesh>& getMeshes() const noexcept { return meshes; }
private:
	void loadModel(const char* filepath);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

private:
	std::vector<Mesh> meshes;
	std::string directory;

	std::vector<Texture2D> loadedTextures;
};

}