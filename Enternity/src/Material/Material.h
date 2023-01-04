#pragma once
#include "Macro/Macro.h"
#include "glm/glm.hpp"

BEGIN_ENTERNITY

struct Material
{
	glm::vec4	ambient{ 1.0f };
	glm::vec4	diffuse{ 1.0f };
	glm::vec4	specular{ 1.0f };
};

END_ENTERNITY