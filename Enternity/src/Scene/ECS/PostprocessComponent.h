#pragma once

namespace Enternity
{
	class Mesh;
	class Renderer;
	struct PostprocessComponent
	{
		Mesh* mesh{ nullptr };
		Renderer* renderer{ nullptr };
	};
}