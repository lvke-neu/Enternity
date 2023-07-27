#pragma once
#include <glm/gtc/matrix_transform.hpp>

namespace Enternity
{
	struct PointLightComponent
	{
		glm::vec3 position{ 0.0f };
		glm::vec3 color{ 1.0f };
	};
}