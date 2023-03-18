#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace Enternity
{
	class Texture2D;
	struct PhongMaterial
	{
		Texture2D* ambient;
		Texture2D* diffuse;
		Texture2D* specular;
		float shininess;
	};
}