#pragma once

namespace Enternity
{
	class Mesh;
	class Renderer;
	class Texture2D;
	struct PostProcessComponent
	{
		Mesh* mesh{ nullptr };
		Renderer* renderer{ nullptr };
		Texture2D* texture2D{ nullptr };
	};
}
