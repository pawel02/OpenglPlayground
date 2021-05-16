#pragma once
#include "../../Core/VertexArray.hpp"

namespace Engine
{
namespace Meshes
{
// These are the vertices
    static float simpleCube[216] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	// positions      
	static float Cube[288] = {
		// positions          // normals           // texture coords
		-1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,  //back
		 1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
		 1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
		 1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
		-1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,

		-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,	0.0f,  0.0f, 0.0f,  //left
		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,	0.0f,  0.0f, 1.0f,
		-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,	0.0f,  1.0f, 1.0f,
		-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,	0.0f,  1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,	0.0f,  1.0f, 0.0f,
		-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,	0.0f,  0.0f, 0.0f,

		 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  //right
		 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,

		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,  //front
		 1.0f, -1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-1.0f,  1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,  //top
		-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,

		 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,  //bottom
		-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	};

	static VertexArray<float, unsigned int> createSimpleCube()
	{
		return VertexArray<float, unsigned int>(
			simpleCube, sizeof(simpleCube),
			{
				VertexAttribLayout{3, GL_FLOAT, GL_FALSE, 3 * sizeof(float)}
			}
		);
	}

	static VertexArray<float, unsigned int> createCube()
	{
		return VertexArray<float, unsigned int>(
			Cube, sizeof(Cube),
			{
				VertexAttribLayout{3, GL_FLOAT, GL_FALSE, 8 * sizeof(float)},
				VertexAttribLayout{3, GL_FLOAT, GL_FALSE, 8 * sizeof(float)},
				VertexAttribLayout{2, GL_FLOAT, GL_FALSE, 8 * sizeof(float)},
			}
		);
	}
}; // NAMESPACE MESHES
}  // NAMESPACE ENGINE