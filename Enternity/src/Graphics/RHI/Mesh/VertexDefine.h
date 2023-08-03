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

		static std::vector<Layout> s_layout;
	};

#define MAX_BONE_INFLUENCE 4

	struct Vertex_Skeleton
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texcoord;

		int m_boneIDs[MAX_BONE_INFLUENCE] = {-1, -1, -1, -1};

		float m_weights[MAX_BONE_INFLUENCE] = { -1.0f, -1.0f, -1.0f, -1.0f };

		static std::vector<Layout> s_layout;
	};
}

