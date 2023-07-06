#pragma once

namespace Enternity
{
	class Mesh;
	class Renderer;
	struct Visual3DComponent
	{
		enum EnvironmentMapType
		{
			None,
			Reflection,
			Refraction
		};

		Mesh* mesh{ nullptr };
		Renderer* renderer{ nullptr };
		EnvironmentMapType environmentMapType{ EnvironmentMapType::None };

		void release();
	};
}