#pragma once

namespace Enternity
{
	class Mesh;
	class Renderer;
	class TextureCubeMapHDR;
	struct SkyBoxComponent
	{
		Mesh* mesh{ nullptr };
		Renderer* renderer{ nullptr };
		TextureCubeMapHDR* textureCubeMapHDR{ nullptr };

		void load(const char* texturePath);
		void unload();
		void draw();
	};
}
