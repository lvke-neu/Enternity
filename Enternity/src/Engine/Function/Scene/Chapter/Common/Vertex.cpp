#include "Vertex.h"

namespace Enternity
{
	VertexBufferLayout VertexPosColor::vertexBufferLayout;
	void VertexPosColor::Init()
	{
		if (0 == vertexBufferLayout.getElements().size())
		{
			vertexBufferLayout.push({ 0, 3, GL_FLOAT, false,  6 * sizeof(float), 0 });
			vertexBufferLayout.push({ 1, 3, GL_FLOAT, false,  6 * sizeof(float), 3 * sizeof(float) });
		}
	}
}