#pragma once
#include <stb_image.h>
#include <vector>
#include <string>
#include <glm/glm.hpp>

namespace Engine
{
	/*
Wrapper for the texture0
*/
	class Texture2D
	{
	private:
		struct TextureData
		{
			std::string _filepath;
			glm::vec2 _texWrap;
			glm::vec2 _texFiltering;

			unsigned int buffer;
			unsigned char* texData = nullptr;
			int width, height, nChannels;

			const char* texture_name;
		};

		std::vector<TextureData> _data;

	public:
		Texture2D() noexcept {};
		Texture2D(const char* filepath);
		Texture2D(const char* filepath, const glm::vec2 texWrap, const glm::vec2 texFiltering);

		Texture2D(const Texture2D& other) noexcept;
		Texture2D(Texture2D&& other) noexcept;

		~Texture2D();

		void add_texture(const char* filepath);
		void add_texture(const char* filepath, const glm::vec2 texWrap, const glm::vec2 texFiltering);

		void add_texture_data(TextureData data)
		{
			_data.emplace_back(data);
		}

		inline const std::vector<TextureData>& get_textures() const noexcept { return _data; };

		void bindAll();

	private:
		//loads the latest texture in the _data
		void load_texture();

	};
}
