#pragma once

namespace Enternity
{
	class Mesh;
	class Renderer;
	class TextureCubeMap;
	class TextureCubeMapHDR;
	struct SkyBoxComponent
	{
		Mesh* mesh{ nullptr };
		Renderer* renderer{ nullptr };
		TextureCubeMap* textureCubeMap{ nullptr };
		TextureCubeMapHDR* textureCubeMapHDR{ nullptr };

		void draw();
		void release();
	};
}
