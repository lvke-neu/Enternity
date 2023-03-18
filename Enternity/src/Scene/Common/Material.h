#pragma once

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