#include "Vertex.h"
#include <glad/glad.h>

namespace Enternity
{
	VertexBufferLayout VertexPosColor::vertexBufferLayout(
		{
			{ 0, 3, GL_FLOAT, false,  6 * sizeof(float), 0 },
			{1, 3, GL_FLOAT, false,  6 * sizeof(float), 3 * sizeof(float)}
		}
	);
}