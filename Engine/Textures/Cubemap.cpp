#include "Cubemap.hpp"
#include <stb_image.h>
#include <stdio.h>

namespace Engine{
	void Cubemap::loadCubemap() noexcept
	{
		_VAO.CreateVertexArray();
		glGenTextures(1, &_cubemapTex);
		glBindTexture(GL_TEXTURE_CUBE_MAP, _cubemapTex);

		int width, height, nChannels;
		for (unsigned int i = 0; i < _faces.size(); i++)
		{
			stbi_set_flip_vertically_on_load(false);
			unsigned char* data = stbi_load(_faces[i], &width, &height, &nChannels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			}
			else
			{
				printf("Failed to load cubemap\n");
			}
			stbi_image_free(data);

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		}

		bind();
		_program.setUniform1i("skybox", 0);
	}

	void Cubemap::bind() noexcept
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, _cubemapTex);
	}

	void Cubemap::draw() noexcept
	{
		glDepthFunc(GL_LEQUAL);

		_program.bind();
		_VAO.bind();

		bind();

		//get rid of the translation on the view matrix
		glm::mat4 viewProjection{ 1.0f };
		cameraMatricies matricies = _camera->getMatricies();

		matricies.view = glm::mat4(glm::mat3(matricies.view));
		viewProjection = matricies.projection * matricies.view;
		_program.setUniformMat4f("viewProjection", viewProjection);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glDepthFunc(GL_LESS);
	}
}
