#pragma once
#include <glad/glad.h>

#include <vector>
#include <unordered_map>

#include <glm/glm.hpp>

struct ShaderStruct
{
    int shaderType;
    const char* shaderFile;
};

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

    Shader(const Shader& other) noexcept;
    Shader(Shader&& other) noexcept;

    Shader& operator=(const Shader& other) noexcept;
    Shader& operator=(Shader&& other) noexcept;

    void addShader(int shaderType, const char* shaderFile) noexcept;
    //convinience function to help with adding multiple shaders at once
    void addShader(std::initializer_list<ShaderStruct> shaders) noexcept;

    /*
    Creates the program and deletes the shaders
    */
    void createProgram() noexcept;
    unsigned int getProgram() const noexcept { return _program; }
    void bind() const noexcept { glUseProgram(_program); };

//all of the possible uniforms
public:
	void setUniformMat4f(const char* uniformName, const glm::mat4& matrix);

	void setUniform4f(const char* uniformName, float x, float y, float z, float w) noexcept;
	void setUniform4f(const char* uniformName, glm::vec4& vec) noexcept;

	void setUniform3f(const char* uniformName, float x, float y, float z) noexcept;
    void setUniform3f(const char* uniformName, glm::vec3& vec) noexcept;
	
	void setUniform1i(const char* uniformName, int i);
	void setUniform1f(const char* uniformName, float i);

private:
	int getUniformLocation(const char* uniformName) noexcept;

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