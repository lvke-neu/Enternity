#pragma once

namespace Enternity
{
	class Mesh;
	class Renderer;
	struct PostProcessComponent
	{
		Mesh* mesh{ nullptr };
		Renderer* renderer{ nullptr };

		void draw(unsigned int textureId);
		void release();
	};
}
