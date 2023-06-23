#pragma once

namespace Enternity
{
	class Mesh;
	class Renderer;
	struct Visual3DComponent
	{
		Mesh* mesh{ nullptr };
		Renderer* renderer{ nullptr };
	};
}