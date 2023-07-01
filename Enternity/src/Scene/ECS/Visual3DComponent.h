#pragma once

namespace Enternity
{
	enum class EnvironmentMapType
	{
		None,
		Reflection,
		Refraction
	};

	class Mesh;
	class Renderer;
	struct Visual3DComponent
	{
		Mesh* mesh{ nullptr };
		Renderer* renderer{ nullptr };
		EnvironmentMapType environmentMapType{ EnvironmentMapType::None };

		void release();
	};
}