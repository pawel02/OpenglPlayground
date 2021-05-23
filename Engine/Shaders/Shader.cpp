#include "Shader.hpp"
#include <fstream>
#include <stdio.h>

#include <glm/gtc/type_ptr.hpp>

namespace Engine
{

Shader::Shader(const char* vertexFile, const char* fragmentFile) noexcept
{
    addShader({ 
        ShaderStruct{GL_VERTEX_SHADER, vertexFile},
        ShaderStruct{GL_FRAGMENT_SHADER, fragmentFile}
    });

    createProgram();
}

Shader::Shader(const std::string& vertexFile, const std::string& fragmentFile) noexcept
{
    addShader({
        ShaderStruct{GL_VERTEX_SHADER, vertexFile.c_str()},
        ShaderStruct{GL_FRAGMENT_SHADER, fragmentFile.c_str()}
        });

    createProgram();
}


Shader::Shader(const char* vertexFile, const char* geometryFile, const char* fragmentFile) noexcept
{
    addShader({
        ShaderStruct{GL_VERTEX_SHADER, vertexFile},
        ShaderStruct{GL_GEOMETRY_SHADER, geometryFile},
        ShaderStruct{GL_FRAGMENT_SHADER, fragmentFile}
        });

    createProgram();
}

Shader::Shader(const std::string& vertexFile, const std::string& geometryFile, const std::string& fragmentFile) noexcept
{
    addShader({
        ShaderStruct{GL_VERTEX_SHADER, vertexFile.c_str()},
        ShaderStruct{GL_GEOMETRY_SHADER, geometryFile.c_str()},
        ShaderStruct{GL_FRAGMENT_SHADER, fragmentFile.c_str()}
        });

    createProgram();
}



Shader::Shader(const Shader& other) noexcept
    :_shaders{other._shaders},
    _program{other._program},
    uniformLocations{other.uniformLocations}
{
}

Shader::Shader(Shader&& other) noexcept
    :_shaders{ std::move(other._shaders) },
    _program{ other._program },
    uniformLocations{ std::move(other.uniformLocations) }
{
}

Shader& Shader::operator=(const Shader& other) noexcept
{
    return Shader{*this};
}

Shader& Shader::operator=(Shader&& other) noexcept
{
    if (this != &other)
    {
        _shaders = std::move(other._shaders);
        _program = other._program;
        uniformLocations = std::move(other.uniformLocations);
    }
    return *this;
}

void Shader::addShader(std::initializer_list<ShaderStruct> shaders) noexcept
{
    for(const auto& shader : shaders)
    {
        addShader(shader.shaderType, shader.shaderFile);
    }
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

    deleteShaders();
    bind();
}
//define all of the uniforms
int Shader::getUniformLocation(const char* uniformName) noexcept
{
    //making sure that the program is bound
    bind();
    if (uniformLocations.find(uniformName) != uniformLocations.end())
    {
        return uniformLocations.at(uniformName);
    }

    int uniformLocation = glGetUniformLocation(_program, uniformName);
    uniformLocations.insert(std::pair<const char*, int>{ uniformName, uniformLocation});
#ifdef _DEBUG
    if (uniformLocation < 0)
    {
        assert("Could not find the unifrom");
    }
#endif

    return uniformLocation;
}

void Shader::setUniformMat4f(const char* uniform_name, const glm::mat4& matrix)
{
	int uniform_location = getUniformLocation(uniform_name);
	glUniformMatrix4fv(uniform_location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setUniform4f(const char* uniform_name, float x, float y, float z, float w) noexcept
{
	int uniform_location = getUniformLocation(uniform_name);
	glUniform4f(uniform_location, x, y, z, w);
}

void Shader::setUniform4f(const char* uniform_name, glm::vec4& vec) noexcept
{
	int uniform_location = getUniformLocation(uniform_name);
	glUniform4f(uniform_location, vec.x, vec.y, vec.z, vec.w);
}

void Shader::setUniform3f(const char* uniform_name, float x, float y, float z) noexcept
{
	int uniform_location = getUniformLocation(uniform_name);
	glUniform3f(uniform_location, x, y, z);
}
void Shader::setUniform3f(const char* uniform_name, glm::vec3& vec) noexcept
{
	int uniform_location = getUniformLocation(uniform_name);
	glUniform3f(uniform_location, vec.x, vec.y, vec.z);
}

void Shader::setUniform1i(const char* uniform_name, int i)
{
	int uniform_location = getUniformLocation(uniform_name);
	glUniform1i(uniform_location, i);
}

void Shader::setUniform1f(const char* uniform_name, float i)
{
	int uniform_location = getUniformLocation(uniform_name);
	glUniform1f(uniform_location, i);
}

}