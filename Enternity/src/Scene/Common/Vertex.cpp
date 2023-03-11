#include "Vertex.h"
#include <glad/glad.h>

namespace Enternity
{
	VertexBufferLayout VertexPosColor::vertexBufferLayout(
		{
			{ 0, 3, GL_FLOAT, false,  6 * sizeof(float), 0 },
			{ 1, 3, GL_FLOAT, false,  6 * sizeof(float), 3 * sizeof(float)}
		}
	);

	VertexBufferLayout VertexPosColorTexcoord::vertexBufferLayout(
		{
			{ 0, 3, GL_FLOAT, false,  8 * sizeof(float), 0 },
			{ 1, 3, GL_FLOAT, false,  8 * sizeof(float), 3 * sizeof(float)},
			{ 2, 2, GL_FLOAT, false,  8 * sizeof(float), 6 * sizeof(float)}
		}
	);
}