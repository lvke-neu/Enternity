#pragma once
#include <glm/glm.hpp>
#include <vector>

namespace Enternity
{
	struct Layout
	{
		unsigned int index;
		unsigned int count;
		unsigned int type;
		bool normalized;
		int stride;
		long long start;
	};



	struct Vertex_Positon_Normal_Texcoord
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texcoord;

		static std::vector<Layout> layouts;
	};
}

