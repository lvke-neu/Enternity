#pragma once
#include <glm/gtc/matrix_transform.hpp>

namespace Enternity
{
	struct SunLightComponent
	{
		glm::vec3 direction{ 0.0f };
		glm::vec3 color{ 1.0f };
	};
}