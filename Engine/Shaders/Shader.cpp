#include "Shader.hpp"
#include <fstream>
#include <stdio.h>

#include <glm/gtc/type_ptr.hpp>

namespace Engine
{

Shader::Shader(const char* vertexFile, const char* fragmentFile) noexcept
{
    addShader(GL_VERTEX_SHADER, vertexFile);
    addShader(GL_FRAGMENT_SHADER, fragmentFile);
}

/*
Loads the file into memory
Compiles the shader
If DEBUG options are on then it will display debug information
*/
void Shader::addShader(int shaderType, const char* shaderFile) noexcept
{
    std::ifstream file(shaderFile);
    if(file.is_open())
    {
        std::string shaderSource((std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>());

        unsigned int shader = glCreateShader(shaderType);
        _shaders.emplace_back(shader);
        const char* source = shaderSource.c_str();

        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);

#ifdef _DEBUG
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        assert(infoLog);
    }
#endif

    }
    else
    {
        printf("Could not open the shader file %s", shaderFile);
    }

}

void Shader::deleteShaders() noexcept
{
    for(const auto& shader : _shaders)
    {
        glDeleteShader(shader);
    }

    //make sure that these shaders no longer have references
    _shaders.clear();
}

void Shader::createProgram() noexcept
{
    _program = glCreateProgram();

    for(const auto& shader : _shaders)
    {
        glAttachShader(_program, shader);
    }

    glLinkProgram(_program);
#ifdef _DEBUG
    glGetProgramiv(_program, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(_program, 512, NULL, infoLog);
        assert(infoLog);
    }

#endif

    bind();
}

void Shader::set_uniform_mat4f(const char* uniform_name, const glm::mat4& matrix)
{
	int uniform_location = get_uniform_location(uniform_name);
	glUniformMatrix4fv(uniform_location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::set_uniform_4f(const char* uniform_name, float x, float y, float z, float w) noexcept
{
	int uniform_location = get_uniform_location(uniform_name);
	glUniform4f(uniform_location, x, y, z, w);
}

void Shader::set_uniform_4f(const char* uniform_name, glm::vec4& vec) noexcept
{
	int uniform_location = get_uniform_location(uniform_name);
	glUniform4f(uniform_location, vec.x, vec.y, vec.z, vec.w);
}

void Shader::set_uniform_3f(const char* uniform_name, float x, float y, float z) noexcept
{
	int uniform_location = get_uniform_location(uniform_name);
	glUniform3f(uniform_location, x, y, z);
}
void Shader::set_uniform_3f(const char* uniform_name, glm::vec3& vec) noexcept
{
	int uniform_location = get_uniform_location(uniform_name);
	glUniform3f(uniform_location, vec.x, vec.y, vec.z);
}

void Shader::set_uniform_1i(const char* uniform_name, int i)
{
	int uniform_location = get_uniform_location(uniform_name);
	glUniform1i(uniform_location, i);
}

void Shader::set_uniform_1f(const char* uniform_name, float i)
{
	int uniform_location = get_uniform_location(uniform_name);
	glUniform1f(uniform_location, i);
}

}