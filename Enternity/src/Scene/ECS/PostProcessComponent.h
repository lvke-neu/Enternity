#pragma once

namespace Enternity
{
	class Mesh;
	class Renderer;
	struct PostProcessComponent
	{
		Mesh* mesh{ nullptr };
		Renderer* renderer{ nullptr };

		void draw();
		void release();
	};
}
