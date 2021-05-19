#pragma once
#include "../../Core/VertexArray.hpp"

namespace Engine
{
namespace Meshes
{
// These are the vertices
    static float simplePlane[18] = {
		-1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f
	};

	// positions      
	static float Plane[48] = {
		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-1.0f,  1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	};

	static VertexArray<float, unsigned int> createSimplePlane()
	{
		return VertexArray<float, unsigned int>(
			simplePlane, sizeof(simplePlane),
			{
				VertexAttribLayout{3, GL_FLOAT, GL_FALSE, 3 * sizeof(float)}
			}
		);
	}

    static VertexArray<float, unsigned int> createPlane()
	{
		return VertexArray<float, unsigned int>(
			Plane, sizeof(Plane),
			{
				VertexAttribLayout{3, GL_FLOAT, GL_FALSE, 8 * sizeof(float)},
				VertexAttribLayout{3, GL_FLOAT, GL_FALSE, 8 * sizeof(float)},
				VertexAttribLayout{2, GL_FLOAT, GL_FALSE, 8 * sizeof(float)},
			}
		);
	}
}; // NAMESPACE MESHES
}  // NAMESPACE ENGINE