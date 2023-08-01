#include "VertexDefine.h"
#include <glad/glad.h>

namespace Enternity
{
	std::vector<Layout> Vertex_Positon_Normal_Texcoord::s_layout
	{
		{ 0, 3, GL_FLOAT, false,  8 * sizeof(float), 0 },
		{ 1, 3, GL_FLOAT, false,  8 * sizeof(float), 3 * sizeof(float) },
		{ 2, 2, GL_FLOAT, false,  8 * sizeof(float), 6 * sizeof(float) }
	};

	std::vector<Layout> Vertex_Skeleton::s_layout
	{
		{ 0, 3, GL_FLOAT, false,  (8 + MAX_BONE_INFLUENCE) * sizeof(float) + MAX_BONE_INFLUENCE * sizeof(int), 0 },
		{ 1, 3, GL_FLOAT, false, (8 + MAX_BONE_INFLUENCE) * sizeof(float) + MAX_BONE_INFLUENCE * sizeof(int), 3 * sizeof(float) },
		{ 2, 2, GL_FLOAT, false,  (8 + MAX_BONE_INFLUENCE) * sizeof(float) + MAX_BONE_INFLUENCE * sizeof(int), 6 * sizeof(float) },
		{ 3, MAX_BONE_INFLUENCE, GL_INT, false,  (8 + MAX_BONE_INFLUENCE) * sizeof(float) + MAX_BONE_INFLUENCE * sizeof(int), 8 * sizeof(float) },
		{ 4, MAX_BONE_INFLUENCE, GL_FLOAT, false,  (8 + MAX_BONE_INFLUENCE) * sizeof(float) + MAX_BONE_INFLUENCE * sizeof(int), 8 * sizeof(float) + 4 * sizeof(int) }
	};
}