#pragma once
#include <glm/gtc/matrix_transform.hpp>

namespace Enternity
{
	struct PBRMaterialComponent
	{
		glm::vec3 albedo{ 1.0f };
		float metallic = 0.0f;
		float roughness = 0.0f;
		float ao = 1.0f;
	};
}