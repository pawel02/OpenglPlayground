#pragma once
#include <glad/glad.h>
#include "Debugging.hpp"
#include "../Shaders/Shader.hpp"
#include "../Assets/Meshes/Planes.hpp"

namespace Engine
{
class Framebuffer
{
public:
	enum class FramebufferStatus : uint8_t
	{
		success = 0,
		fail
	};

	struct FramebufferStruct
	{
		FramebufferStatus status;
		std::shared_ptr<Framebuffer> fbo;
	};


	Framebuffer(int width, int height, Shader&& program)
		:_width{ width }, _height{ height },
		_VAO{ std::move(Meshes::createPlane()) },
		_program{ std::move(program) }
	{
		glGenFramebuffers(1, &_buffer);
		glBindFramebuffer(GL_FRAMEBUFFER, _buffer);
		_VAO.CreateVertexArray();
	}

	Framebuffer(Framebuffer&& other) noexcept
		:_buffer{ other._buffer },
		_rbo{ other._rbo },
		_texture{ other._texture },
		_width{ other._width },
		_height{ other._height },
		_VAO{std::move(other._VAO)},
		_program{std::move(other._program)}
	{}

	Framebuffer& operator=(Framebuffer&& other) noexcept
	{
		if (this != &other)
		{
			_buffer = other._buffer;
			_rbo = other._rbo;
			_texture = other._texture;
			_width = other._width;
			_height = other._height;
			_VAO = std::move(other._VAO);
			_program = std::move(other._program);
		}
		return *this;
	}

	~Framebuffer() = default;

	void bind() const noexcept
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _buffer);
	}

	void draw() const noexcept
	{
		//draw to the default framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		//clear all the buffers
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);

		//draw the texture in the window
		_VAO.bind();
		_program.bind();

		//bind the textures
		glBindTexture(GL_TEXTURE_2D, _texture);
		glActiveTexture(GL_TEXTURE0);

		glCheckError(glDrawArrays(GL_TRIANGLES, 0, 6));

		glEnable(GL_DEPTH_TEST);
	}

	FramebufferStatus init()
	{
		glGenTextures(1, &_texture);
		glBindTexture(GL_TEXTURE_2D, _texture);

		//create an empty texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		//bind the texture to the framebuffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture, 0);

		//create render buffer for stencil and depth testing
		glGenRenderbuffers(1, &_rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);

		//attach the renderbuffer
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rbo);

		//unbind everything
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);


		//make sure everything was created successfully
		//make sure the framebuffer was created successfully
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			return FramebufferStatus::fail;

		return FramebufferStatus::success;
	}

private:
	unsigned int _buffer;
	unsigned int _rbo = 0;
	unsigned int _texture = 0;

	int _width;
	int _height;

	VertexArray<float, unsigned int> _VAO;
	Shader _program;
};

}