#pragma once
#include <glad/glad.h>

#include <vector>
#include <unordered_map>

#include <glm/glm.hpp>

/*
Basic shader abstraction
Use example
Shader()
Shader::addShader
Shader::createProgram
*/
namespace Engine
{

class Shader
{
public:
    Shader() noexcept {};
    Shader(const char* vertexFile, const char* fragmentFile) noexcept;

    void addShader(int shaderType, const char* shaderFile) noexcept;

    /*
    Creates the program and deletes the shaders
    */
    void createProgram() noexcept;
    void bind() const noexcept { glUseProgram(_program); };

//all of the possible uniforms
public:
	void set_uniform_mat4f(const char* uniform_name, const glm::mat4& matrix);

	void set_uniform_4f(const char* uniform_name, float x, float y, float z, float w) noexcept;
	void set_uniform_4f(const char* uniform_name, glm::vec4& vec) noexcept;

	void set_uniform_3f(const char* uniform_name, float x, float y, float z) noexcept;
    void set_uniform_3f(const char* uniform_name, glm::vec3& vec) noexcept;
	
	void set_uniform_1i(const char* uniform_name, int i);
	void set_uniform_1f(const char* uniform_name, float i);

private:
	int get_uniform_location(const char* uniform_name) noexcept;

private:
    void deleteShaders() noexcept;

private:
    std::vector<unsigned int> _shaders;
    unsigned int _program = 0;

    int success = 0;
    char infoLog[512] = "";
    std::unordered_map<const char*, int> uniformLocations;
};

}