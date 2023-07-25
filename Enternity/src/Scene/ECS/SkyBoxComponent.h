#pragma once

namespace Enternity
{
	class Mesh;
	class Renderer;
	class TextureCubeMap;
	struct SkyBoxComponent
	{
		Mesh* mesh{ nullptr };
		Renderer* renderer{ nullptr };
		TextureCubeMap* textureCubeMap{ nullptr };

		void draw();
		void release();
	};
}
