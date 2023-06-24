#pragma once

namespace Enternity
{
	class Mesh;
	class Renderer;
	class Texture;
	struct Visual3DComponent
	{
		Mesh* mesh{ nullptr };
		Renderer* renderer{ nullptr };
	};
}