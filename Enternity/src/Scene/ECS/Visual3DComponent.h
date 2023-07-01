#pragma once

namespace Enternity
{
	class Mesh;
	class Renderer;
	struct Visual3DComponent
	{
		Mesh* mesh{ nullptr };
		Renderer* renderer{ nullptr };
		bool enableEnvironmentMap{ false };
		void release();
	};
}