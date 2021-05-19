#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Texture2D.hpp"

namespace Engine
{

	Texture2D::Texture2D(const char* filepath)
	{
		stbi_set_flip_vertically_on_load(true);
		addTexture(filepath);
	}

	Texture2D::Texture2D(const char* filepath,
		const glm::vec2 texWrap,
		const glm::vec2 texFiltering)
	{
		addTexture(filepath, texWrap, texFiltering);
	}

	Texture2D::Texture2D(const Texture2D& other) noexcept
	{
		_data = other._data;
	}

	Texture2D::Texture2D(Texture2D&& other) noexcept
		:_data{ std::move(other._data) }
	{}


	Texture2D::~Texture2D()
	{
	}

	void Texture2D::addTexture(const std::string& filepath)
	{
		_data.emplace_back(TextureData{
			filepath,
			{ GL_REPEAT, GL_REPEAT },
			{ GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR }
			});

		loadTexture();
	}

	void Texture2D::addTexture(const std::string& filepath, const glm::vec2 texWrap, const glm::vec2 texFiltering)
	{
		_data.emplace_back(TextureData{
			filepath,
			{ texWrap },
			{ texFiltering }
			});

		loadTexture();
	}

	void Texture2D::bindAll()
	{
		for (int i = 0; i < _data.size(); ++i)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, _data[i].buffer);
		}
	}

	void Texture2D::loadTexture()
	{
		stbi_set_flip_vertically_on_load(true);
		const auto data = _data.end() - 1;

		data->texData = stbi_load(data->_filepath.c_str(), &data->width, &data->height, &data->nChannels, 0);
		if (data->texData != nullptr)
		{
			//load the texture into graphics card
			glGenTextures(1, &data->buffer);

			//assign this to the next texture spot
			glActiveTexture(GL_TEXTURE0 + static_cast<int>(_data.size() - 1));
			glBindTexture(GL_TEXTURE_2D, data->buffer);

			//wrapping
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, data->_texWrap.x);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, data->_texWrap.y);

			//filtering
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, data->_texFiltering.x);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, data->_texFiltering.y);

			GLenum format = GL_RGB;
			if (data->nChannels == 1)
				format = GL_RED;
			else if (data->nChannels == 3)
				format = GL_RGB;
			else if (data->nChannels == 4)
				format = GL_RGBA;
			glTexImage2D(GL_TEXTURE_2D, 0, format, data->width, data->height, 0, format, GL_UNSIGNED_BYTE, data->texData);
			glGenerateMipmap(GL_TEXTURE_2D);

			//clear the memory for the image as its on the GPU now
			stbi_image_free(data->texData);
			data->texData = nullptr;
		}
		else
		{
			std::cout << "Could not load the texture " << data->_filepath << "\n";
		}
	}
}
